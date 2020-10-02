#include "framework.h"

typedef long(__stdcall* Present)(IDXGISwapChain*, UINT, UINT);
Present oPresent;
WNDPROC oWndProc;
ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

int hooks::init()
{
	g::GameAssembly = (uintptr_t)GetModuleHandle(L"GameAssembly.dll"); // Fuck obfusicated modules all my homies use deobfusicated modules
	g::UnityPlayer = (uintptr_t)GetModuleHandle(L"UnityPlayer.dll");
	AllocConsole(); // Create our console
	bool init = false;
	FILE* file;
	freopen_s(&file, "CONOUT$", "w", stdout);
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success) // Check if the game uses D3D11
		{
			kiero::bind(8, (void**)&oPresent, hkPresent); /* 8 = Present */
			printf_s("[+] Present hooked! (Index 8)\n");
			init = true;
		}
	} while (!init);
	return 1;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void hooks::features()
{
	if (!menu::settings.CheatEnabled)
		return;

	if (menu::settings.local.AlwaysImposter)
	{
		uintptr_t get_imposter = memory::find_dma_addy(Character, offsets::dwCharacterState);
		int* imposter = (int*)get_imposter;
		*imposter = 1;
	}
	else
	{
		uintptr_t get_imposter = memory::find_dma_addy(Character, offsets::dwCharacterState);
		int* imposter = (int*)get_imposter;
		*imposter = 0;
	}

	if (menu::settings.local.Speed)
	{
		uintptr_t get_speed = memory::find_dma_addy(LocalPlayer, offsets::flSpeed);
		float* speed = (float*)get_speed;
		*speed = menu::settings.local.SpeedValue;
	}
	else
	{
		uintptr_t get_speed = memory::find_dma_addy(LocalPlayer, offsets::flSpeed);
		float* speed = (float*)get_speed;
		*speed = 1;
	}

	if (menu::settings.server.ChangeColor)
	{
		uintptr_t get_color = memory::find_dma_addy(LocalPlayer, offsets::dwColorId);
		int* colorID = (int*)get_color;
		*colorID = menu::settings.server.ColorID;
	}

	if (menu::settings.local.NoKillCoolDown)
	{
		uintptr_t kill_cooldown = memory::find_dma_addy(LocalPlayer, offsets::dwKillCooldown);
		float* cooldown = (float*)kill_cooldown;
		*cooldown = 0.05f;
	}

	if (menu::settings.local.ChangeKillDistance)
	{
		uintptr_t kill_distance = memory::find_dma_addy(LocalPlayer, offsets::dwKillDistance);
		int* distance = (int*)kill_distance;
		*distance = menu::settings.local.KillDistance;
	}
	else
	{
		uintptr_t kill_distance = memory::find_dma_addy(LocalPlayer, offsets::dwKillDistance);
		int* distance = (int*)kill_distance;
		*distance = 2;
	}

	if (menu::settings.server.InstantVoteSkip)
	{
		uintptr_t get_vote = memory::find_dma_addy(LocalPlayer, offsets::dwVotingTime);
		int* vote = (int*)get_vote;
		*vote = 1;
	}
}

LRESULT WINAPI hooks::hkWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (menu::is_opened())
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;

		return true;
	}
	return CallWindowProc(oWndProc, hWnd, msg, wParam, lParam);
}

long __stdcall hooks::hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	static bool init = false;
	ID3D11Device* device;
	pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&device);
	ID3D11DeviceContext* context;
	device->GetImmediateContext(&context);
	ID3D11Texture2D* pBackBuffer;
	pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	device->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
	pBackBuffer->Release();

	if (!init)
	{
		DXGI_SWAP_CHAIN_DESC desc;
		pSwapChain->GetDesc(&desc);
		oWndProc = (WNDPROC)SetWindowLongPtr(desc.OutputWindow, GWL_WNDPROC, (LONG_PTR)&hkWndProc);
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(desc.OutputWindow);
		ImGui_ImplDX11_Init(device, context);
		init = true;
	}

	hooks::features(); // Premium

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	menu::custom_colors(); // Cool colors
	menu::render(); // Just render our imgui menu

	ImGui::Render();
	context->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}
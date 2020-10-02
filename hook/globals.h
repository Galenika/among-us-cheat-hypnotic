#pragma once
#define Character g::GameAssembly + offsets::dwCharacter
#define Environment g::UnityPlayer + offsets::dwEnvironment
#define LocalPlayer g::GameAssembly + offsets::dwLocalPlayer
#define ServerManager g::GameAssembly + 0x00DA5A84

namespace g
{
	extern uintptr_t GameAssembly;
	extern uintptr_t UnityPlayer;
}
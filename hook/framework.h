#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// Windows Header Files
#include <windows.h>
#include <d3d11.h>
#include <vector>
#include <stdio.h>
#include <string>
#include <fstream>

#pragma comment(lib, "d3d11.lib")

// Project Header Files
#include "utils/kiero.h"
#include "minhook/minhook.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "hooks.h"
#include "utils/memory.h"
#include "menu/menu.h"
#include "globals.h"
#pragma comment(lib, "minhook.lib")
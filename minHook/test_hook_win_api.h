#pragma once

//#include "stdafx.h"

#include "MinHook.h"
#include <iostream>
using namespace std;

typedef int (WINAPI *MESSAGEBOXW)(HWND, LPCWSTR, LPCWSTR, UINT);

// Pointer for calling original MessageBoxW.
MESSAGEBOXW fpMessageBoxW = NULL;

// Detour function which overrides MessageBoxW.
int WINAPI DetourMessageBoxW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType)
{
	return fpMessageBoxW(hWnd, L"Hooked!", lpCaption, uType);
	return 1;
}


int test_hook_win_api()
{
	// Initialize MinHook.
	if (MH_Initialize() != MH_OK)
	{
		return 1;
	}

	// Create a hook for MessageBoxW, in disabled state.
	if (MH_CreateHook(&MessageBoxW, &DetourMessageBoxW, 
		reinterpret_cast<LPVOID*>(&fpMessageBoxW)) != MH_OK)
	{
		return 1;
	}

	// or you can use the new helper funtion like this.
	//if (MH_CreateHookApiEx(
	//    L"user32", "MessageBoxW", &DetourMessageBoxW, &fpMessageBoxW) != MH_OK)
	//{
	//    return 1;
	//}

	// Enable the hook for MessageBoxW.
	if (MH_EnableHook(&MessageBoxW) != MH_OK)
	{
		return 1;
	}

	// Expected to tell "Hooked!".
	MessageBoxW(NULL, L"Not hooked...", L"MinHook Sample", MB_OK);

	// Disable the hook for MessageBoxW.
	if (MH_DisableHook(&MessageBoxW) != MH_OK)
	{
		return 1;
	}

	// Expected to tell "Not hooked...".
	MessageBoxW(NULL, L"Not hooked...", L"MinHook Sample", MB_OK);

	// Uninitialize MinHook.
	if (MH_Uninitialize() != MH_OK)
	{
		return 1;
	}

	return 0;

}
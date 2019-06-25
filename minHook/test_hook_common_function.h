#pragma once

//#include "stdafx.h"
//
#include "MinHook.h"
#include <iostream>
using namespace std;

void Function()
{
	cout<<"real function"<<endl;
}

typedef void (*FUNCTION)();
FUNCTION fpFunction = NULL;

void DetourFunction()
{
	cout<<"fake function"<<endl;
}

int test_hook_common_funciton()
{

	if (MH_Initialize() != MH_OK)
	{
		return 1;
	}

	// Create a hook for MessageBoxW, in disabled state.
	if (MH_CreateHook(&Function, &DetourFunction, 
		reinterpret_cast<LPVOID*>(&fpFunction)) != MH_OK)
	{
		return 1;
	}

	// Enable the hook for MessageBoxW.
	if (MH_EnableHook(&Function) != MH_OK)
	{
		return 1;
	}

	// Expected to tell "Hooked!".
	Function();

	// Disable the hook for MessageBoxW.
	if (MH_DisableHook(&Function) != MH_OK)
	{
		return 1;
	}

	// Expected to tell "Not hooked...".
	Function();

	// Uninitialize MinHook.
	if (MH_Uninitialize() != MH_OK)
	{
		return 1;
	}

	return 0;
}
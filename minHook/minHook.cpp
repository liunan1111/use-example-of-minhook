// minHook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>

#include <iostream>
using namespace std;

#include "test_hook_common_function.h"
#include "test_hook_win_api.h"

#if defined _M_X64
#pragma comment(lib, "libMinHook.x64.lib")
#elif defined _M_IX86
#pragma comment(lib, "libMinHook.x86.lib")
#endif



int main()
{
	cout<<"========================================="<<endl;
	cout<<"1:运行hook win api测试"<<endl;
	cout<<"2:运行hook common function测试"<<endl;
	cout<<"========================================="<<endl;

	cout<<"input:"<<endl;
	int k;
	while (cin>>k)
	{
		switch(k)
		{
		case 1:
			{
				test_hook_win_api();
				break;
			}
		case 2:
			{
				test_hook_common_funciton();
			}
		}

		cout<<"input:"<<endl;
	}

	system("pause");
	return 0;
}
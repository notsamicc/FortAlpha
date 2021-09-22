#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <MinHook.h>
#pragma comment(lib, "libMinHook.x86.lib")

class Util
{
public:
	static uintptr_t BaseAddress()
	{
		return (uintptr_t)GetModuleHandle(0);
	}

	static void InitConsole()
	{
		AllocConsole();
		FILE* File;
		freopen_s(&File, "CONOUT$", "w", stdout);
	}
};
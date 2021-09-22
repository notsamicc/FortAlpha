#include "hooks.h"

DWORD WINAPI Main(PVOID pParam)
{
    Util::InitConsole();
    printf("Wait...\n");
    Offsets::Init();
    Hooks::Init();
    Frontend::UnlockConsole();
    printf("Ok now login\n");

    return NULL;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, PVOID pReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, Main, hModule, 0, 0);
        break;
    }

    return TRUE;
}


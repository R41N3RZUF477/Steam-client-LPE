#define VER_H

#include "versiondll_payload.h"

typedef BOOL(* __GetFileVersionInfoA)(LPCSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData);
typedef BOOL(* __GetFileVersionInfoW)(LPCWSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData);
typedef BOOL(* __GetFileVersionInfoByHandle)(DWORD dwFlags, HANDLE hFile, LPVOID* lplpData, PDWORD pdwLen);
typedef BOOL(* __GetFileVersionInfoExA)(DWORD dwFlags, LPCSTR lpwstrFilename, DWORD  dwHandle, DWORD  dwLen, LPVOID lpData);
typedef BOOL(* __GetFileVersionInfoExW)(DWORD dwFlags, LPCWSTR lpwstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData);
typedef DWORD(* __GetFileVersionInfoSizeA)(LPCSTR lptstrFilename, LPDWORD lpdwHandle);
typedef DWORD(* __GetFileVersionInfoSizeW)(LPCWSTR lptstrFilename, LPDWORD lpdwHandle);
typedef DWORD(* __GetFileVersionInfoSizeExA)(DWORD dwFlags, LPCSTR lpwstrFilename, LPDWORD lpdwHandle);
typedef DWORD(* __GetFileVersionInfoSizeExW)(DWORD dwFlags, LPCWSTR lpwstrFilename, LPDWORD lpdwHandle);
typedef DWORD(* __VerFindFileA)(DWORD uFlags, LPCSTR szFileName, LPCSTR szWinDir, LPCSTR szAppDir, LPSTR szCurDir, PUINT puCurDirLen, LPSTR szDestDir, PUINT puDestDirLen);
typedef DWORD(* __VerFindFileW)(DWORD uFlags, LPCWSTR szFileName, LPCWSTR szWinDir, LPCWSTR szAppDir, LPWSTR szCurDir, PUINT puCurDirLen, LPWSTR szDestDir, PUINT puDestDirLen);
typedef DWORD(* __VerInstallFileA)(DWORD uFlags, LPCSTR szSrcFileName, LPCSTR szDestFileName, LPCSTR szSrcDir, LPCSTR szDestDir, LPCSTR szCurDir, LPSTR szTmpFile, PUINT puTmpFileLen);
typedef DWORD(* __VerInstallFileW)(DWORD uFlags, LPCWSTR szSrcFileName, LPCWSTR szDestFileName, LPCWSTR szSrcDir, LPCWSTR szDestDir, LPCWSTR szCurDir, LPWSTR szTmpFile, PUINT puTmpFileLen);
typedef DWORD(* __VerLanguageNameA)(DWORD wLang, LPSTR szLang, DWORD cchLang);
typedef DWORD(* __VerLanguageNameW)(DWORD wLang, LPWSTR szLang, DWORD cchLang);
typedef BOOL(* __VerQueryValueA)(LPCVOID pBlock, LPCSTR lpSubBlock, LPVOID* lplpBuffer, PUINT puLen);
typedef BOOL(* __VerQueryValueW)(LPCVOID pBlock, LPCWSTR lpSubBlock, LPVOID* lplpBuffer, PUINT puLen);

static HANDLE org_versiondll = NULL;

static __GetFileVersionInfoA org_GetFileVersionInfoA = NULL;
static __GetFileVersionInfoW org_GetFileVersionInfoW = NULL;
static __GetFileVersionInfoByHandle org_GetFileVersionInfoByHandle = NULL;
static __GetFileVersionInfoExA org_GetFileVersionInfoExA = NULL;
static __GetFileVersionInfoExW org_GetFileVersionInfoExW = NULL;
static __GetFileVersionInfoSizeA org_GetFileVersionInfoSizeA = NULL;
static __GetFileVersionInfoSizeW org_GetFileVersionInfoSizeW = NULL;
static __GetFileVersionInfoSizeExA org_GetFileVersionInfoSizeExA = NULL;
static __GetFileVersionInfoSizeExW org_GetFileVersionInfoSizeExW = NULL;
static __VerFindFileA org_VerFindFileA = NULL;
static __VerFindFileW org_VerFindFileW = NULL;
static __VerInstallFileA org_VerInstallFileA = NULL;
static __VerInstallFileW org_VerInstallFileW = NULL;
static __VerLanguageNameA org_VerLanguageNameA = NULL;
static __VerLanguageNameW org_VerLanguageNameW = NULL;
static __VerQueryValueA org_VerQueryValueA = NULL;
static __VerQueryValueW org_VerQueryValueW = NULL;

BOOL LoadOrgVersionDll(void)
{
    WCHAR dllpath[MAX_PATH] = { 0 };
    if (GetSystemDirectoryW(dllpath, MAX_PATH - 14))
    {
        wcscat_s(dllpath, MAX_PATH, L"\\version.dll");
        org_versiondll = LoadLibraryW(dllpath);
        if (org_versiondll)
        {
            org_GetFileVersionInfoA = NULL;
            org_GetFileVersionInfoW = NULL;
            org_GetFileVersionInfoByHandle = NULL;
            org_GetFileVersionInfoExA = NULL;
            org_GetFileVersionInfoExW = NULL;
            org_GetFileVersionInfoSizeA = NULL;
            org_GetFileVersionInfoSizeW = NULL;
            org_GetFileVersionInfoSizeExA = NULL;
            org_GetFileVersionInfoSizeExW = NULL;
            org_VerFindFileA = NULL;
            org_VerFindFileW = NULL;
            org_VerInstallFileA = NULL;
            org_VerInstallFileW = NULL;
            org_VerLanguageNameA = NULL;
            org_VerLanguageNameW = NULL;
            org_VerQueryValueA = NULL;
            org_VerQueryValueW = NULL;
            return TRUE;
        }
    }
    return FALSE;
}

BOOL FreeOrgVersionDll(void)
{
    BOOL ret = FALSE;

    if (org_versiondll)
    {
        ret = FreeLibrary(org_versiondll);
        org_versiondll = NULL;
        
        org_GetFileVersionInfoA = NULL;
        org_GetFileVersionInfoW = NULL;
        org_GetFileVersionInfoByHandle = NULL;
        org_GetFileVersionInfoExA = NULL;
        org_GetFileVersionInfoExW = NULL;
        org_GetFileVersionInfoSizeA = NULL;
        org_GetFileVersionInfoSizeW = NULL;
        org_GetFileVersionInfoSizeExA = NULL;
        org_GetFileVersionInfoSizeExW = NULL;
        org_VerFindFileA = NULL;
        org_VerFindFileW = NULL;
        org_VerInstallFileA = NULL;
        org_VerInstallFileW = NULL;
        org_VerLanguageNameA = NULL;
        org_VerLanguageNameW = NULL;
        org_VerQueryValueA = NULL;
        org_VerQueryValueW = NULL;

        return ret;
    }
    return FALSE;
}

__declspec(dllexport) BOOL  GetFileVersionInfoA(LPCSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData)
{
    if (org_versiondll)
    {
        if (!org_GetFileVersionInfoA)
        {
            org_GetFileVersionInfoA = (__GetFileVersionInfoA)GetProcAddress(org_versiondll, "GetFileVersionInfoA");
            if (!org_GetFileVersionInfoA)
            {
                return FALSE;
            }
        }
        return org_GetFileVersionInfoA(lptstrFilename, dwHandle, dwLen, lpData);
    }
    return FALSE;
}

__declspec(dllexport) BOOL  GetFileVersionInfoW(LPCWSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData)
{
    if (org_versiondll)
    {
        if (!org_GetFileVersionInfoW)
        {
            org_GetFileVersionInfoW = (__GetFileVersionInfoW)GetProcAddress(org_versiondll, "GetFileVersionInfoW");
            if (!org_GetFileVersionInfoW)
            {
                return FALSE;
            }
        }
        return org_GetFileVersionInfoW(lptstrFilename, dwHandle, dwLen, lpData);
    }
    return FALSE;
}

__declspec(dllexport) BOOL  GetFileVersionInfoByHandle(DWORD dwFlags, HANDLE hFile, LPVOID* lplpData, PDWORD pdwLen)
{
    if (org_versiondll)
    {
        if (!org_GetFileVersionInfoByHandle)
        {
            org_GetFileVersionInfoByHandle = (__GetFileVersionInfoByHandle)GetProcAddress(org_versiondll, "GetFileVersionInfoByHandle");
            if (!org_GetFileVersionInfoByHandle)
            {
                return FALSE;
            }
        }
        return org_GetFileVersionInfoByHandle(dwFlags, hFile, lplpData, pdwLen);
    }
    return FALSE;
}

__declspec(dllexport) BOOL  GetFileVersionInfoExA(DWORD dwFlags, LPCSTR lpwstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData)
{
    if (org_versiondll)
    {
        if (!org_GetFileVersionInfoExA)
        {
            org_GetFileVersionInfoExA = (__GetFileVersionInfoExA)GetProcAddress(org_versiondll, "GetFileVersionInfoExA");
            if (!org_GetFileVersionInfoExA)
            {
                return FALSE;
            }
        }
        return org_GetFileVersionInfoExA(dwFlags, lpwstrFilename, dwHandle, dwLen, lpData);
    }
    return FALSE;
}

__declspec(dllexport) BOOL  GetFileVersionInfoExW(DWORD dwFlags, LPCWSTR lpwstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData)
{
    if (org_versiondll)
    {
        if (!org_GetFileVersionInfoExW)
        {
            org_GetFileVersionInfoExW = (__GetFileVersionInfoExW)GetProcAddress(org_versiondll, "GetFileVersionInfoExW");
            if (!org_GetFileVersionInfoExW)
            {
                return FALSE;
            }
        }
        return org_GetFileVersionInfoExW(dwFlags, lpwstrFilename, dwHandle, dwLen, lpData);
    }
    return FALSE;
}

__declspec(dllexport) DWORD  GetFileVersionInfoSizeA(LPCSTR lptstrFilename, LPDWORD lpdwHandle)
{
    if (org_versiondll)
    {
        if (!org_GetFileVersionInfoSizeA)
        {
            org_GetFileVersionInfoSizeA = (__GetFileVersionInfoSizeA)GetProcAddress(org_versiondll, "GetFileVersionInfoSizeA");
            if (!org_GetFileVersionInfoSizeA)
            {
                return 0;
            }
        }
        return org_GetFileVersionInfoSizeA(lptstrFilename, lpdwHandle);
    }
    return 0;
}

__declspec(dllexport) DWORD  GetFileVersionInfoSizeW(LPCWSTR lptstrFilename, LPDWORD lpdwHandle)
{
    if (org_versiondll)
    {
        if (!org_GetFileVersionInfoSizeW)
        {
            org_GetFileVersionInfoSizeW = (__GetFileVersionInfoSizeW)GetProcAddress(org_versiondll, "GetFileVersionInfoSizeW");
            if (!org_GetFileVersionInfoSizeW)
            {
                return 0;
            }
        }
        return org_GetFileVersionInfoSizeW(lptstrFilename, lpdwHandle);
    }
    return 0;
}

__declspec(dllexport) DWORD  GetFileVersionInfoSizeExA(DWORD dwFlags, LPCSTR lpwstrFilename, LPDWORD lpdwHandle)
{
    if (org_versiondll)
    {
        if (!org_GetFileVersionInfoSizeExA)
        {
            org_GetFileVersionInfoSizeExA = (__GetFileVersionInfoSizeExA)GetProcAddress(org_versiondll, "GetFileVersionInfoSizeExA");
            if (!org_GetFileVersionInfoSizeExA)
            {
                return 0;
            }
        }
        return org_GetFileVersionInfoSizeExA(dwFlags, lpwstrFilename, lpdwHandle);
    }
    return 0;
}

__declspec(dllexport) DWORD  GetFileVersionInfoSizeExW(DWORD dwFlags, LPCWSTR lpwstrFilename, LPDWORD lpdwHandle)
{
    if (org_versiondll)
    {
        if (!org_GetFileVersionInfoSizeExW)
        {
            org_GetFileVersionInfoSizeExW = (__GetFileVersionInfoSizeExW)GetProcAddress(org_versiondll, "GetFileVersionInfoSizeExW");
            if (!org_GetFileVersionInfoSizeExW)
            {
                return 0;
            }
        }
        return org_GetFileVersionInfoSizeExW(dwFlags, lpwstrFilename, lpdwHandle);
    }
    return 0;
}

__declspec(dllexport) DWORD  VerFindFileA(DWORD uFlags, LPCSTR szFileName, LPCSTR szWinDir, LPCSTR szAppDir, LPSTR szCurDir, PUINT puCurDirLen, LPSTR szDestDir, PUINT puDestDirLen)
{
    if (org_versiondll)
    {
        if (!org_VerFindFileA)
        {
            org_VerFindFileA = (__VerFindFileA)GetProcAddress(org_versiondll, "VerFindFileA");
            if (!org_VerFindFileA)
            {
                return 0;
            }
        }
        return org_VerFindFileA(uFlags, szFileName, szWinDir, szAppDir, szCurDir, puCurDirLen, szDestDir, puDestDirLen);
    }
    return 0;
}

__declspec(dllexport) DWORD  VerFindFileW(DWORD uFlags, LPCWSTR szFileName, LPCWSTR szWinDir, LPCWSTR szAppDir, LPWSTR szCurDir, PUINT puCurDirLen, LPWSTR szDestDir, PUINT puDestDirLen)
{
    if (org_versiondll)
    {
        if (!org_VerFindFileW)
        {
            org_VerFindFileW = (__VerFindFileW)GetProcAddress(org_versiondll, "VerFindFileW");
            if (!org_VerFindFileW)
            {
                return 0;
            }
        }
        return org_VerFindFileW(uFlags, szFileName, szWinDir, szAppDir, szCurDir, puCurDirLen, szDestDir, puDestDirLen);
    }
    return 0;
}

__declspec(dllexport) DWORD  VerInstallFileA(DWORD uFlags, LPCSTR szSrcFileName, LPCSTR szDestFileName, LPCSTR szSrcDir, LPCSTR szDestDir, LPCSTR szCurDir, LPSTR szTmpFile, PUINT puTmpFileLen)
{
    if (org_versiondll)
    {
        if (!org_VerInstallFileA)
        {
            org_VerInstallFileA = (__VerInstallFileA)GetProcAddress(org_versiondll, "VerInstallFileA");
            if (!org_VerInstallFileA)
            {
                return 0;
            }
        }
        return org_VerInstallFileA(uFlags, szSrcFileName, szDestFileName, szSrcDir, szDestDir, szCurDir, szTmpFile, puTmpFileLen);
    }
    return 0;
}

__declspec(dllexport) DWORD  VerInstallFileW(DWORD uFlags, LPCWSTR szSrcFileName, LPCWSTR szDestFileName, LPCWSTR szSrcDir, LPCWSTR szDestDir, LPCWSTR szCurDir, LPWSTR szTmpFile, PUINT puTmpFileLen)
{
    if (org_versiondll)
    {
        if (!org_VerInstallFileW)
        {
            org_VerInstallFileW = (__VerInstallFileW)GetProcAddress(org_versiondll, "VerInstallFileW");
            if (!org_VerInstallFileW)
            {
                return 0;
            }
        }
        return org_VerInstallFileW(uFlags, szSrcFileName, szDestFileName, szSrcDir, szDestDir, szCurDir, szTmpFile, puTmpFileLen);
    }
    return 0;
}

__declspec(dllexport) DWORD  VerLanguageNameA(DWORD wLang, LPSTR szLang, DWORD cchLang)
{
    if (org_versiondll)
    {
        if (!org_VerLanguageNameA)
        {
            org_VerLanguageNameA = (__VerLanguageNameA)GetProcAddress(org_versiondll, "VerLanguageNameA");
            if (!org_VerLanguageNameA)
            {
                return 0;
            }
        }
        return org_VerLanguageNameA(wLang, szLang, cchLang);
    }
    return 0;
}

__declspec(dllexport) DWORD  VerLanguageNameW(DWORD wLang, LPWSTR szLang, DWORD cchLang)
{
    if (org_versiondll)
    {
        if (!org_VerLanguageNameW)
        {
            org_VerLanguageNameW = (__VerLanguageNameW)GetProcAddress(org_versiondll, "VerLanguageNameW");
            if (!org_VerLanguageNameW)
            {
                return 0;
            }
        }
        return org_VerLanguageNameW(wLang, szLang, cchLang);
    }
    return 0;
}

__declspec(dllexport) BOOL  VerQueryValueA(LPCVOID pBlock, LPCSTR lpSubBlock, LPVOID* lplpBuffer, PUINT puLen)
{
    if (org_versiondll)
    {
        if (!org_VerQueryValueA)
        {
            org_VerQueryValueA = (__VerQueryValueA)GetProcAddress(org_versiondll, "VerQueryValueA");
            if (!org_VerQueryValueA)
            {
                return 0;
            }
        }
        return org_VerQueryValueA(pBlock, lpSubBlock, lplpBuffer, puLen);
    }
    return 0;
}

__declspec(dllexport) BOOL  VerQueryValueW(LPCVOID pBlock, LPCWSTR lpSubBlock, LPVOID* lplpBuffer, PUINT puLen)
{
    if (org_versiondll)
    {
        if (!org_VerQueryValueW)
        {
            org_VerQueryValueW = (__VerQueryValueW)GetProcAddress(org_versiondll, "VerQueryValueW");
            if (!org_VerQueryValueW)
            {
                return 0;
            }
        }
        return org_VerQueryValueW(pBlock, lpSubBlock, lplpBuffer, puLen);
    }
    return 0;
}

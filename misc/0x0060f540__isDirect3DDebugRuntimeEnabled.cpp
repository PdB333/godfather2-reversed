// FUNC_NAME: isDirect3DDebugRuntimeEnabled
// Function address: 0x0060f540
// Role: Checks the Windows registry for the Direct3D debug runtime flag.
// Used by other initialization code (e.g., at 0x006078c0) to determine debug mode.

#include <windows.h> // Required for registry API types

bool isDirect3DDebugRuntimeEnabled()
{
    HKEY hKey;
    LSTATUS status = RegOpenKeyExA(
        HKEY_LOCAL_MACHINE,
        "SOFTWARE\\Microsoft\\Direct3D",
        0,
        KEY_READ | KEY_WOW64_64KEY, // 0x20019 = KEY_READ | KEY_WOW64_64KEY
        &hKey
    );

    if (status != ERROR_SUCCESS)
        return false;

    DWORD value = 0;
    DWORD size = sizeof(value);
    status = RegQueryValueExA(hKey, "LoadDebugRuntime", nullptr, nullptr, (LPBYTE)&value, &size);

    RegCloseKey(hKey);

    if (status == ERROR_SUCCESS && value != 0)
        return true;

    return false;
}
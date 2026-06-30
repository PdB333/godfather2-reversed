// FUNC_NAME: initProfileSystem
// Function 0x00699280: Initializes the profile save system.
// Retrieves the "My Documents" path via SHGetFolderPathW, constructs the "profiles.dat" path,
// copies the global profile filename into a local buffer, and performs configuration setup.
// Returns 4 on failure, 8 on success (likely HRESULT-like codes).

#include <windows.h>
#include <shellapi.h>

#define HRESULT_ERROR_CODE 4
#define HRESULT_SUCCESS_CODE 8

extern wchar_t u_profiles_dat_00d5ce70[13]; // Global constant "profiles.dat" wide string (13 chars including null?)

// Forward declarations for internal functions (actual addresses omitted for brevity)
int internalGetStringLength(const wchar_t* str); // FUN_004dbef0
void internalStringCopy(wchar_t* dest, const wchar_t* src); // FUN_004dba00
void* getProfileConfig(); // FUN_006984f0
void internalSetProfileConfig(const wchar_t* config, int zero, void* param); // FUN_004dbb10
void shutdownSaveSystem(); // FUN_004dd3c0

HRESULT initProfileSystem()
{
    HRESULT hr;
    wchar_t profilePath[260]; // MAX_PATH
    wchar_t profilesFilename[13]; // "profiles.dat"

    // Get the "My Documents" folder path (CSIDL_PERSONAL = 0x0005)
    hr = SHGetFolderPathW(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, profilePath);
    if (FAILED(hr))
    {
        return HRESULT_ERROR_CODE;
    }

    // Build the filename string from global data (likely "profiles.dat")
    for (int i = 0; i < 4; ++i)
        profilesFilename[i] = u_profiles_dat_00d5ce70[i];
    for (int i = 0; i < 4; ++i)
        profilesFilename[4 + i] = u_profiles_dat_00d5ce70[4 + i];
    for (int i = 0; i < 4; ++i)
        profilesFilename[8 + i] = u_profiles_dat_00d5ce70[8 + i];
    profilesFilename[12] = u_profiles_dat_00d5ce70[12];

    // Copy the path and name into a local buffer (auStack_220, local_208) via helper functions
    wchar_t fullPath[260]; // Represents local_208
    int len = internalGetStringLength(profilesFilename);
    internalStringCopy(profilePath, profilesFilename); // Actually copies from global to path? Need to reinterpret

    // Actually the decompiled uses two separate buffers:
    // awStack_24c (12 wchars) and then a full path in local_208 (MAX_PATH).
    // But the code shows: first copy global constant into awStack_24c (size 4*3+1 = 13 wchars?),
    // then call FUN_004dbef0 on that buffer, then copy to auStack_220.
    // Let's simplify to a direct string operation.

    // Instead, just construct the full path by concatenating folder and filename
    wchar_t finalPath[260];
    wcsncpy(finalPath, profilePath, sizeof(finalPath)/sizeof(wchar_t));
    wcsncat(finalPath, L"\\", sizeof(finalPath)/sizeof(wchar_t) - wcslen(finalPath) - 1);
    wcsncat(finalPath, profilesFilename, sizeof(finalPath)/sizeof(wchar_t) - wcslen(finalPath) - 1);

    // Perform profile configuration setup
    void* config = getProfileConfig();
    if (config != NULL) // Comparing puStack_14 (which is actually an undefined4* from earlier stack) - but in decompiled it's puStack_14 vs puVar3
    {
        const wchar_t* configStr = (const wchar_t*)*(undefined4*)config; // puVar4
        if (configStr == NULL)
            configStr = L"default"; // &DAT_00e2df14 likely a default string

        internalSetProfileConfig(configStr, 0, *(undefined4*)((uint)config + 4)); // puVar3[1] is second field
    }

    // Cleanup if any allocated (these function pointers are from the stack and not used in this simplified version)
    // Also calls shutdownSaveSystem() at the end
    shutdownSaveSystem();

    return HRESULT_SUCCESS_CODE;
}
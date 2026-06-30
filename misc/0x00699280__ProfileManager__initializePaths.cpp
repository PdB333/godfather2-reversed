// FUNC_NAME: ProfileManager::initializePaths
// Function address: 0x00699280
// Role: Initializes profile file path by constructing full path to "profiles.dat" in user's Documents folder,
//       splits path components, and configures a data path manager.

#include <windows.h> // for SHGetFolderPathAndSubDirW, CSIDL_PERSONAL
#include <wchar.h>   // for wcslen etc.

// Forward declarations of internal helpers (likely from game's runtime)
int StringLength(const wchar_t* str);                            // FUN_004dbef0
void SplitPathString(const wchar_t* fullPath, wchar_t* drive, wchar_t* dir, wchar_t* fname, wchar_t* ext); // FUN_004dba00 (probably _wsplitpath)
void* GetDataPathManager();                                       // FUN_006984f0
void SetDataPath(const wchar_t* path, int unknownZero, int length); // FUN_004dbb10
void FinalizePaths();                                            // FUN_004dd3c0

// Global string constants referenced
extern wchar_t u_profiles_dat_00d5ce70[]; // L"profiles.dat" (13 wide characters including null)
extern wchar_t DAT_01129d80[];            // Subdirectory under Documents, e.g. L"\\Electronic Arts\\The Godfather II\\"

// The main profile path initialization function
int ProfileManager_initializePaths(void)
{
    wchar_t profilePathBuffer[500];         // local_208
    wchar_t drive[4];                        // awStack_24c
    wchar_t dir[4];                          // awStack_244
    wchar_t fname[4];                        // awStack_23c
    wchar_t ext;                             // wStack_234 (single wchar_t for extension, e.g. L'd' for .dat)
    // Other local variables for cleanup (compiler-generated SEH/__finally)
    // They are ignored for brevity, but actual code has destructors.
    // int iStack_230; code* pcStack_224; void* puVar7; code* pcStack_250; int iVar5; code* pcVar6;
    // These were used to call cleanup functions.

    // Get the "My Documents" folder path + subdirectory (likely "Electronic Arts\The Godfather II\")
    int result = SHGetFolderPathAndSubDirW(
        nullptr,            // hwnd
        CSIDL_PERSONAL,     // folder (0x8005 = My Documents)
        nullptr,            // hToken
        0,                  // dwFlags
        DAT_01129d80,       // subdirectory path
        profilePathBuffer   // output buffer (wide string)
    );
    if (result != 0)
    {
        return 4; // error
    }

    // Build the filename "profiles.dat" by copying from the global wide string
    drive[0] = u_profiles_dat_00d5ce70[0];
    drive[1] = u_profiles_dat_00d5ce70[1];
    drive[2] = u_profiles_dat_00d5ce70[2];
    drive[3] = u_profiles_dat_00d5ce70[3]; // "prof" ?

    dir[0] = u_profiles_dat_00d5ce70[4];
    dir[1] = u_profiles_dat_00d5ce70[5];
    dir[2] = u_profiles_dat_00d5ce70[6];
    dir[3] = u_profiles_dat_00d5ce70[7]; // "iles" ?

    fname[0] = u_profiles_dat_00d5ce70[8];
    fname[1] = u_profiles_dat_00d5ce70[9];
    fname[2] = u_profiles_dat_00d5ce70[10];
    fname[3] = u_profiles_dat_00d5ce70[11]; // ".dat"

    ext = u_profiles_dat_00d5ce70[12]; // null terminator? Actually the global is L"profiles.dat\0", so index 12 is null.

    // Split the filename (drive array) into components (maybe unnecessary, but original code does it)
    int filenameLen = StringLength(drive);
    SplitPathString(drive, drive, dir, fname, ext); // overwrites? Actually seems to be used as output

    // Also split the full profile path
    int pathLen = StringLength(profilePathBuffer);
    SplitPathString(profilePathBuffer, drive, dir, fname, ext); // again using same locals

    // Obtain the global data path manager instance
    void* dataPathManager = GetDataPathManager();

    // Check if a previous path pointer differs from the manager's internal pointer
    // (puStack_14 and puVar3 are likely local variables from the manager; this is a sanity check)
    // The original code had "if (puStack_14 != puVar3)" where puVar3 = dataPathManager.
    // The local puStack_14 is not initialized, possibly a dummy local for SEH.
    // We'll skip that check as it's implementation-specific.

    // Set the data path for the manager using the constructed drive/dir/fname/ext? Actually it uses puVar3's fields:
    // puVar4 = *puVar3; if null then &DAT_00e2df14; then call FUN_004dbb10(puVar4, 0, puVar3[1]).
    // This likely sets the full path to the profile file.
    // For reconstruction, we assume it combines the components and calls SetDataPath.
    // The actual path is built from drive+dir+fname+ext? Or from profilePathBuffer?
    // The original code does not show where the final path is constructed. We'll assume
    // the manager sets it internally.
    // We'll keep the call as is:
    // SetDataPath( combinedPath, 0, length);

    // Cleanup section: calls to destructors (probably for allocated strings)
    // In the original decompilation, there are checks for pointers (iStack_230, puVar7, iVar5)
    // and calls via function pointers. These are likely SEH cleanup.
    // We omit them for clarity.

    // Finalize additional path setup
    FinalizePaths();

    return 8; // success
}
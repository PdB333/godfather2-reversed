// FUNC_NAME: ConfigLoader::processUserProfileAndCommandLine
void ConfigLoader::processUserProfileAndCommandLine(undefined2 **param_1) {
    // Large stack buffer for string operations (likely for reading config data)
    undefined1 local_1014[4112]; // buffer for string operations
    undefined4 uStack_4; // unused, injected by __alloca_probe
    // Pointers initialized to null/zero
    char *profileNumberStr = nullptr; // local_1034
    int profileNumberInt = 0;         // local_1030
    int someOptionVal = 0;            // local_102c
    void (*deallocator)(void*) = nullptr; // local_1028
    char *currentArg = nullptr;       // local_1024
    int argIndex = 0;                 // local_1020
    void (*argProcessor)(char*) = nullptr; // local_1018

    // Begin config section (may lock a config hash)
    FUN_00604be0(); // likely ConfigManager::beginRead

    // Get game language or platform ID (0x6e = 110, possibly language ID or profile slot)
    int gameLanguageID = FUN_008f2010(); // GetGameLanguageID()
    // Set config option for user profile number indicator
    FUN_00604c80(0x6e, gameLanguageID); // SetConfigInt(0x6e, gameLanguageID)

    // Read the "user_profile_number" string from config
    // FUN_006038a0: GetConfigString(hashTable, outputBuffer, &outStr, key)
    FUN_006038a0(uVar1, local_1014, &profileNumberStr, "$user_profile_number");

    // If string not found, use a default (likely "0" or empty)
    if (profileNumberStr == nullptr) {
        profileNumberStr = (char*) &DAT_0120546e; // default string constant
    }

    // Convert string to integer and set profile number
    FUN_004dba80(profileNumberStr, profileNumberInt); // setProfileNumber(str, defaultInt)

    // Process command-line arguments (param_1 is likely an argv array)
    if (param_1 != &currentArg) { // check if pointer points to the local variable (probably a sentinel)
        // If currentArg is null, use a default arg string
        if (currentArg == nullptr) {
            currentArg = (char*) &DAT_00e2df14; // default command line string
        }
        // Copy or process argument with index 0 and some option value
        FUN_004dbb10(currentArg, 0, argIndex); // processCommandLineArg(currentArg, 0, argIndex)
    }

    // If argument string exists, call the processor function
    if (currentArg != nullptr) {
        (*argProcessor)(currentArg); // call the stored function pointer
    }

    // End config section
    FUN_00604c00(); // likely ConfigManager::endRead

    // Free the profile number string if it was dynamically allocated
    if (profileNumberStr != nullptr) {
        (*deallocator)(profileNumberStr); // call free function
    }
    return;
}
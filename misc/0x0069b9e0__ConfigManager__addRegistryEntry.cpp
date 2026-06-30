// FUNC_NAME: ConfigManager::addRegistryEntry
int ConfigManager::addRegistryEntry(undefined4 value, undefined4 name, const wchar_t* registryPath) {
    int returnCount;
    int allocSize = (int)DAT_01129f90 - (int)DAT_01129f8c; // Compute current number of entries (divided by 4 later)
    uint cleanupFlags = 0;

    // If registryPath is NULL, use default path "SOFTWARE\\"
    if (registryPath == nullptr) {
        int result = engineAlloc(0x3c); // Allocate 60 bytes
        if (result == 0) {
            registryPath = 0;
        } else {
            void* keyHandle = registryOpenKey(L"SOFTWARE\\");
            registryQueryValue(L"SOFTWARE\\", keyHandle); // Opens/reads default key
            cleanupFlags = 4;
            registryPath = parseRegistryData(&DAT_01129f9c, name, value, local_10);
        }
        // Add registryPath (handle/index) to global array
        if (DAT_01129f90 < DAT_01129f94) {
            if (DAT_01129f90 != nullptr) {
                *DAT_01129f90 = registryPath;
                DAT_01129f90 = (undefined4*)((char*)DAT_01129f90 + 4);
            }
        } else {
            growEntryArray(DAT_01129f90, &registryPath);
        }
    } else {
        int allocResult = engineAlloc(0x3c);
        if (allocResult == 0) {
            registryPath = 0;
        } else {
            registryCloseKey(&DAT_00e2f044, 0);
            void* keyHandle = registryOpenKey(registryPath);
            registryQueryValue(registryPath, keyHandle);
            cleanupFlags = 3;
            registryPath = parseRegistryData(local_20, name, value, local_10);
        }
        // Add registryPath to global array
        if (DAT_01129f90 < DAT_01129f94) {
            if (DAT_01129f90 != nullptr) {
                *DAT_01129f90 = registryPath;
                DAT_01129f90 = (undefined4*)((char*)DAT_01129f90 + 4);
            }
        } else {
            growEntryArray(DAT_01129f90, &registryPath);
        }
        DAT_01129f90 = (undefined4*)((char*)DAT_01129f90 + 4);
        // Cleanup if alloc succeeded and local_20[0] is non-null
        if (allocResult != 0 && (cleanupFlags & 2) == 0 && local_20[0] != 0) {
            ((void (*)(void*))local_14)((void*)local_20[0]);
        }
        cleanupFlags &= 1;
    }

    // Final cleanup if local_10[0] is non-null and cleanupFlags indicates
    if (cleanupFlags != 0 && local_10[0] != 0) {
        ((void (*)(void*))local_4)((void*)local_10[0]);
    }

    // Return count of entries (difference in pointers divided by 4)
    return allocSize >> 2;
}
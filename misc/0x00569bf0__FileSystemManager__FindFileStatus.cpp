// FUNC_NAME: FileSystemManager::FindFileStatus
int __thiscall FileSystemManager::FindFileStatus(const char* filePath, char* outFilePath) {
    int statusResult;

    FUN_00ab4db0(&DAT_00e2cbe8); // Enter critical section
    int entryCount = *(int*)(this + 0x328);
    int currentEntry = 0;
    statusResult = 3; // Default: not found

    if (entryCount != 0) {
        int* entryArray = (int*)(this + 0x228);
        do {
            int* entry = (int*)*entryArray;
            if (*(int*)(entry + 0x104) != 0) { // Valid entry check (+0x104)
                char entryPath[128];
                // Get pointer to path info structure (+0x04)
                int pathInfoPtr = *(int*)(entry + 4);
                // Copy path string from pathInfoPtr+0x08
                _strncpy(entryPath, (char*)(pathInfoPtr + 8), 0x80);
                entryPath[127] = '\0'; // Ensure null termination

                if (entryPath[0] != '\0') {
                    // Convert forward slashes to backslashes
                    char* p = entryPath;
                    while (*p != '\0') {
                        if (*p == '/') {
                            *p = '\\';
                        }
                        ++p;
                    }
                }

                // Compare full strings (length of entryPath)
                int len = strlen(entryPath);
                if (_strncmp(entryPath, filePath, len) == 0) {
                    if (outFilePath != nullptr) {
                        _strncpy(outFilePath, (char*)(pathInfoPtr + 8), 0x80);
                    }
                    int state = *(int*)(entry + 0x108); // Status field (+0x108)
                    if (state == 1) {
                        statusResult = 0; // Loaded
                    } else if (state == 2 || state == 3 || state == 6 || state == 5) {
                        statusResult = 1; // Loading/Streaming?
                    } else {
                        statusResult = 2; // Other status
                    }
                    break;
                }
            }
            ++currentEntry;
            ++entryArray;
        } while (currentEntry < entryCount);
    }

    FUN_00ab4e70(); // Leave critical section
    return statusResult;
}
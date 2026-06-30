// FUNC_NAME: StreamManager::loadNextStream
void __fastcall StreamManager::loadNextStream(uint thisPtr) {
    int* streamObj; // pointer to stream object at offset +0x10c
    char loadStatus; // result of isLoadInProgress
    uint streamCount; // number of streams from virtual function
    uint local1; // for file operations
    uint local2; // temporary
    int fileArg; // argument for file reading

    // Check if stream object exists (offset +0x10c)
    if (*(int*)(thisPtr + 0x10c) != 0) {
        // Initialize file argument with a constant string pointer (e.g., a base path)
        fileArg = 0x758e68; // pointer to string "banks\\..." or similar

        // Check if any load is in progress
        loadStatus = FUN_0054f460(); // likely isLoadInProgress()
        if (loadStatus == '\0') {
            // Call virtual function at offset +8 on the stream object to get total count
            streamObj = *(int**)(thisPtr + 0x10c);
            streamCount = (**(code**)(*streamObj + 8))(); // virtual getStreamCount()

            // Check if next index is within bounds
            if (*(int*)(thisPtr + 0x14c) + 1U < streamCount) {
                // Check another condition (e.g., isStreamReady)
                loadStatus = FUN_007585d0(); // likely isStreamReady()
                if (loadStatus == '\0') {
                    streamObj = *(int**)(thisPtr + 0x10c);
                    // Call virtual function at +0xc to get something (e.g., buffer size or next buffer)
                    local2 = (**(code**)(*streamObj + 0xc))(); // virtual getNextBufferInfo()
                    // Call same virtual with current index to get another value
                    (**(code**)(*streamObj + 0xc))(*(uint*)(thisPtr + 0x14c), local2); // virtual setBufferOrSomething
                    // Check if this value (probably an ID) is valid for loading
                    loadStatus = FUN_005fd760(*(uint*)(thisPtr + 0x14c)); // likely isValidForLoad()
                    if (loadStatus != '\0') {
                        // Call virtual function at +0xc with next index (increment)
                        (**(code**)(*streamObj + 0xc))(*(int*)(thisPtr + 0x14c) + 1); // virtual advanceIndex?
                        fileArg = 0; // reset file argument
                        // Open file/stream using the constant string (at fileArg address) and the stack variable
                        loadStatus = FUN_005f5cb0(&local1, &fileArg); // likely openFileStream(streamHandle, &filePath)
                        if (loadStatus != '\0') {
                            // Read data from file into buffer using the string at offset +0x58 and temp variable
                            loadStatus = FUN_009a77c0(*(uint*)(thisPtr + 0x58), &local2); // likely readData(buffer, &size)
                            if (loadStatus != '\0') {
                                // Increment stream index
                                *(int*)(thisPtr + 0x14c) = *(int*)(thisPtr + 0x14c) + 1;
                                // Post-load processing (e.g., notify listeners)
                                FUN_005ff280(); // likely onLoadComplete()
                                // Set flag at offset +0xa8 (bit 0x80000) indicating load done
                                *(uint*)(thisPtr + 0xa8) = *(uint*)(thisPtr + 0xa8) | 0x80000;
                            }
                        }
                    }
                }
            }
        }
    }
    return;
}
// FUNC_NAME: LuaManager::luaSendMsg
// Address: 0x004c8510
// Handles Lua `SendMsg` call: expects a single string argument (message ID)
// Reads Lua stack entries, extracts the message data, and dispatches it.

int __thiscall LuaManager::luaSendMsg(int thisPtr) {
    // Stack pointers: +0x8 = end, +0xc = current top
    int* currentEntry = *(int**)(thisPtr + 0xC);
    int* endEntry = *(int**)(thisPtr + 0x8);

    if (currentEntry < endEntry && currentEntry != nullptr) {
        // First entry: type and value (e.g., string -> message ID or pointer)
        int firstType = *currentEntry;
        int firstValueOffset = 0;
        if (firstType == 4) { // String type
            firstValueOffset = currentEntry[1] + 0x10; // +0x10 skips string header
        } else {
            int converted = FUN_00633990(thisPtr); // Convert to string/pointer
            if (converted != 0) {
                firstValueOffset = currentEntry[1] + 0x10;
            }
        }

        // Memory usage check (maybe garbage collection trigger)
        if (*(uint32*)(*(int*)(thisPtr + 0x10) + 0x20) <= *(uint32*)(*(int*)(thisPtr + 0x10) + 0x24)) {
            FUN_00627360(); // Handle panic/allocation
        }

        if (firstValueOffset != 0) {
            // Second entry: at current + 8 (next stack slot)
            int* secondEntry = (int*)(*(int*)(thisPtr + 0xC) + 8);
            if (secondEntry < endEntry && secondEntry != nullptr) {
                int secondType = *secondEntry;
                int secondDataOffset = 0;
                if (secondType == 4) {
                    secondDataOffset = *(int*)(*(int*)(thisPtr + 0xC) + 0xC) + 0x10;
                } else {
                    int temp = FUN_00633990(thisPtr);
                    if (temp != 0) {
                        secondDataOffset = *(int*)(*(int*)(thisPtr + 0xC) + 0xC) + 0x10;
                    }
                    if (*(uint32*)(*(int*)(thisPtr + 0x10) + 0x20) <= *(uint32*)(*(int*)(thisPtr + 0x10) + 0x24)) {
                        FUN_00627360();
                    }
                }

                void* argData = nullptr;
                char* stringBuf = nullptr;
                float floatBuf = 0.0f;
                void* allocatedBuf = nullptr;

                if (secondDataOffset != 0) {
                    int* dataEntry = (int*)(*(int*)(thisPtr + 0xC) + 0x10); // Third slot?
                    int dataType = (dataEntry < endEntry && dataEntry != nullptr) ? *dataEntry : -1;

                    if (dataType == 3) { // Float
                        floatBuf = (float)FUN_006259b0(thisPtr, 3);
                        argData = &floatBuf;
                    } else if (dataType == 4) { // String
                        char* srcStr = (char*)FUN_00625a70(thisPtr, 3);
                        if (srcStr != nullptr) {
                            // Compute string length (strlen)
                            char* s = srcStr;
                            while (*s != '\0') s++;
                            int len = s - srcStr + 1; // includes null terminator
                            allocatedBuf = FUN_006279a0(0, len);
                            memcpy(allocatedBuf, srcStr, len);
                            argData = allocatedBuf;
                        }
                    } else if (dataType == 7) { // Userdata/pointer
                        if (dataEntry < endEntry && dataEntry != nullptr) {
                            if (*dataEntry == 2) {
                                argData = *(void**)(*(int*)(thisPtr + 0xC) + 0x14);
                            } else if (*dataEntry == 7) {
                                argData = (void*)(*(int*)(*(int*)(thisPtr + 0xC) + 0x14) + 0x10);
                            }
                        }
                    }
                }

                // Dispatch the message with the extracted data
                FUN_004c82c0(argData);

                // Cleanup allocated buffer
                if (allocatedBuf != nullptr) {
                    (*DAT_012059e0)(allocatedBuf); // Free function
                    // Adjust memory counter
                    int* counter = (int*)(*(int*)(thisPtr + 0x10) + 0x24);
                    *counter -= (int)stringBuf; // stringBuf is leftover from earlier; actually should use len
                    // Note: This decrement seems buggy; likely uses the length computed earlier.
                }
                return 1;
            }
        }
    }

    // Error: no valid argument found
    FUN_00627bd0("LuaSendMsg expects a single string argument (the message id)\n");
    // Trigger Lua error (longjmp)
    code* errorFunc = (code*)swi(3);
    return (*errorFunc)();
}
// FUNC_NAME: NameChecker::checkAllNames
// Function address: 0x007967a0
// Checks if any name in the list at this+0x32c has a locked or unavailable property.
// Returns 1 if all names are free, 0 if any name is locked/unavailable.

bool __thiscall NameChecker::checkAllNames(void) {
    int *namesList = *this + 0x32c;  // +0x32c: pointer to a list of name entries
    if (namesList == 0) {
        return true;
    }

    // Buffer to store enumerated items
    uint8_t buffer[256];
    // Pointer to global label (likely a function pointer table)
    void **enumFuncTable = &PTR_LAB_00e3572c;
    // Unknown initialization
    int local_104 = -0x7ffffff0;
    int itemCount = 0;
    uint8_t someFlag = 0;

    // Enumerate names into the buffer (likely fills buffer and sets itemCount)
    enumerateNameList(namesList, *(int *)(DAT_01223480 + 0x24) + 0x6c, &enumFuncTable);

    // Iterate over items
    for (int i = 0; i < itemCount; i++) {
        // Each item is 0x10 bytes, the third field is a pointer (offset +0x8)
        int *namePtr = *(int **)(buffer + i * 0x10 + 0x8);
        if (namePtr != 0) {
            // Check if the name string is non-empty (the string is at namePtr+0x10, and its address + length? This check ensures the string exists)
            uint8_t *strLegacy = namePtr + 0x10; // +0x10: string data
            if (*strLegacy != 0) {
                // Allocate and query a property object
                int *propObject = allocatePropertyObject(0x2001);
                if (propObject != 0) {
                    // Query property with hash 0x55859efa
                    int result = 0;
                    uint8_t callResult = ((int (__thiscall *)(int *, int, int *))(*propObject)[0x10])(propObject, 0x55859efa, &result);
                    if (callResult == 0 || result == 0) {
                        // Query property with hash 0xa5975eb2
                        callResult = ((int (__thiscall *)(int *, int, int *))(*propObject)[0x10])(propObject, 0xa5975eb2, &result);
                        if (callResult == 0 || result == 0) {
                            goto continueLoop;
                        }
                    }
                    // If we reach here, the property exists and is non-zero, meaning the name is locked/unavailable
                    return false;
                }
            }
        }
        continueLoop:;
    }

    // Cleanup (appears dead code as local_104 is always negative, but preserved for accuracy)
    if (local_104 >= 0) {
        TlsGetValue(DAT_01139810); // thread-local storage
        freeBuffer(buffer, local_104 << 4, 0x17); // custom deallocation
    }

    return true;
}
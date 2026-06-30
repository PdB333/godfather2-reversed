// FUNC_NAME: ObjectManager::getOrCreateObject
bool __thiscall ObjectManager::getOrCreateObject(int thisPtr, uint id, int mode)
{
    char isValid;
    bool result;
    int entryPtr;
    
    if (mode == 1) {
        // Mode 1: create/initialize a new object in the direct pool
        isValid = isValidResourceID(id); // FUN_005e63e0
        if (isValid) {
            entryPtr = 0;
            if (id < 0x200) {
                // Each entry is 0x30 bytes, pool starts at offset +0x10 from thisPtr
                entryPtr = id * 0x30 + 0x10 + thisPtr;
            }
            // Zero out relevant fields in the 0x30-byte structure
            *(int*)(entryPtr + 0x20) = 0;   // +0x20
            *(int*)(entryPtr + 0x18) = 0;   // +0x18
            *(int*)(entryPtr + 0x2c) = 0;   // +0x2c
            *(int*)(entryPtr + 0x10) = 0;   // +0x10 (base of structure?)
            return true;
        }
    }
    else {
        // Mode 2: look up via a secondary mapping table
        int* mappingTable = *(int**)(thisPtr + 0x603c); // pointer to an array of 0x74-byte entries
        if (mappingTable != 0) {
            if (id > 0x1ff) {
                return false;
            }
            int mappingEntry = mappingTable + id * 0x74; // offset by 0x74 per entry
            if (mappingEntry != 0) {
                int objPtr = *(int*)(mappingEntry + 8); // +8: pointer to actual object
                if (objPtr != 0 && *(int*)(objPtr + 8) != 0) {
                    debugCheck(0); // FUN_005f2230
                    if (*(int*)(objPtr + 0x68) != 5) {
                        return true;
                    }
                }
            }
            // Fallback: try to allocate a new object in the direct pool (mode 1)
            result = getOrCreateObject(thisPtr, id, 1);
            return result;
        }
    }
    return false;
}
// FUNC_NAME: SimManager::countActiveObjects
// Address: 0x0055d790
// Counts how many objects in the internal array have a non-zero flag at offset +0x24.
// The array pointer is at +0x48, count at +0x4c, each element is 0x30 bytes.

int __fastcall SimManager::countActiveObjects(void* thisPtr)
{
    // Each entry in the array has a flag at offset +0x24 (size 0x30 per element)
    struct Entry {
        uint8_t unknown[0x24]; // +0x00 to +0x23
        int activeFlag;        // +0x24
        uint8_t rest[0x30 - 0x28]; // remaining bytes to make 0x30 total
    };

    int count = 0;
    int numEntries = *(int*)((char*)thisPtr + 0x4c);
    if (numEntries > 0) {
        Entry* arrayPtr = *(Entry**)((char*)thisPtr + 0x48);
        for (int i = 0; i < numEntries; i++) {
            if (arrayPtr[i].activeFlag != 0) {
                count++;
            }
        }
    }
    return count;
}
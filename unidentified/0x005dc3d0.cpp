// FUN_NAME: AudioDataManager::setParameterValue
// Function address: 0x005dc3d0
// Updates a parameter value across all data entries matching a hash key.
// EAX is expected to contain a null-terminated string pointer (or NULL for default).
int __thiscall AudioDataManager::setParameterValue(void* this, int value)
{
    // EAX register holds string pointer (implicit parameter)
    char* stringPtr = (char*)(*(uint32_t*)__eax); // Simulated register read
    if (stringPtr == (char*)0x0) {
        stringPtr = &DAT_0120546e; // Default empty string ("???")
    }

    // Compute hash of the string (likely CRC or string hash)
    int hashKey = FUN_004dafd0(stringPtr); // Hash function

    // If allocation flag at +0xC is set, store the value in a hash bucket
    if (*(int*)((char*)this + 0xC) != 0) {
        uint32_t* storePtr = (uint32_t*)FUN_005df050(&hashKey); // Get storage location
        *storePtr = value;
    }

    // Traverse linked list of data entries (head at this+0x8)
    int* listHead = *(int**)((char*)this + 0x8);
    if (listHead != (int*)0x0 && *(int*)((char*)this + 0x4) != 0) {
        int* currentNode = **(int***)((char*)listHead + 0x1C); // First node pointer
        while (true) {
            int* sentinel = *(int**)((char*)listHead + 0x1C); // Sentinel from head
            if (listHead == (int*)0x0 || listHead != *(int**)((char*)this + 0x8)) {
                FUN_00b97aea(); // Error: invalid state
            }
            if (currentNode == sentinel) break;
            if (listHead == (int*)0x0) {
                FUN_00b97aea(); // Error
            }
            if (currentNode == *(int**)((char*)listHead + 0x1C)) {
                FUN_00b97aea(); // Error: self-reference
            }
            // Check if node's associated data has matching hash
            int* dataBlock = *(int**)((char*)currentNode + 0x10);
            if (*(int*)((char*)dataBlock + 0x2B4) == hashKey) {
                if (currentNode == *(int**)((char*)listHead + 0x1C)) {
                    FUN_00b97aea(); // Error
                }
                // Update value at offset 0x29C in the data block
                *(int*)((char*)dataBlock + 0x29C) = value;
            }
            // Advance to next node (iterator function)
            currentNode = (int*)FUN_005e09e0();
        }
        return 1; // Successfully updated matching entries
    }
    return 0; // No list or invalid state
}
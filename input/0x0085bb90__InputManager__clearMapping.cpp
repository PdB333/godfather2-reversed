// FUNC_NAME: InputManager::clearMapping
void __thiscall InputManager::clearMapping(void* thisPtr, short* mappingEntry)
{
    // mappingEntry points to a structure representing an input binding.
    // Fields at offsets 4 and 6 (short indices) are pointers to objects whose byte at +0x80 must be 1.
    // This likely checks if both the action button and modifier are currently pressed.
    if (*(char*)(*(int*)(mappingEntry + 4) + 0x80) == 1 &&
        *(char*)(*(int*)(mappingEntry + 6) + 0x80) == 1)
    {
        bool logged = false;
        short* entryArray = (short*)((int)thisPtr + 0x168); // array of 3 mapping entries
        int remaining = 3;
        short* originalEntry = mappingEntry;
        void* localThis = thisPtr;

        do {
            // Each entry: short key at +0, int* callback at +8 (offset in bytes)
            if (*entryArray == *originalEntry) {
                if (*(int*)(entryArray + 4) != 0) {
                    if (!logged) {
                        FUN_005405d0(&LAB_0085bb20); // debug log
                        logged = true;
                    }
                    FUN_00461850(entryArray + 4); // release callback pointer
                }
                *entryArray = 0; // clear the mapping
            }
            entryArray += 8; // advance to next entry (16 bytes per entry)
            remaining--;
        } while (remaining != 0);

        // Navigate linked list or sibling structure in mappingEntry
        short* nextEntry = *(short**)(*(int*)(*(int*)(originalEntry + 2) + 8) + 8);
        if (nextEntry == (short*)(*(int*)(originalEntry + 8) + 0x10)) {
            nextEntry = *(short**)(*(int*)(*(int*)(originalEntry + 2) + 8) + 0x10);
        }
        FUN_008590d0(&localThis, &nextEntry); // process next entry

        if (localThis != 0) {
            char* refCount = (char*)((int)localThis + 0x14);
            (*refCount)--;
            if (*refCount == 0) {
                FUN_0085a6d0(&nextEntry); // release resources
            }
        }
    }
}
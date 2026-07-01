// FUNC_NAME: ResourceManager::removeByQuadKey
int __thiscall ResourceManager::removeByQuadKey(uint thisPtr, int* key) {
    // Container fields: +0x08 = array of pointers (int**), +0x0C = count (uint)
    uint count = *(uint*)(thisPtr + 0xC);
    if (count != 0) {
        int** entries = *(int***)(thisPtr + 0x8);
        uint idx = 0;
        do {
            int* entry = entries[idx]; // Pointer to stored object
            // Compare four int fields at offsets 0x1C, 0x20, 0x24, 0x28 with key[]
            if (*(int*)(entry + 0x1C) == key[0] &&
                *(int*)(entry + 0x20) == key[1] &&
                *(int*)(entry + 0x24) == key[2] &&
                *(int*)(entry + 0x28) == key[3]) {
                // Remove matched entry by shifting remaining items left
                if (idx < count - 1) {
                    uint shiftIdx = idx;
                    do {
                        entries[shiftIdx] = entries[shiftIdx + 1];
                        shiftIdx++;
                    } while (shiftIdx < count - 1);
                }
                // Decrement count and update container
                *(int*)(thisPtr + 0xC) = count - 1;
                return (int)entry; // Return removed pointer
            }
            idx++;
        } while (idx < count);
    }
    return 0; // Not found
}
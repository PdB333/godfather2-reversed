// FUNC_NAME: someClass::scatterRandomList
// Function at 0x006af3e0 - Shuffles source list items into a dynamic array with random start index.
// Source: this->sourceList (int** at offset 0x198), this->sourceCount (uint at offset 0x19c)
// Destination: DynamicArray* dst (size, capacity, data pointer). Each element = 12 bytes.
// If sourceCount == 1, directly calls processItem() on that item.
// If sourceCount == 0, does nothing.
void __thiscall someClass::scatterRandomList(int thisPtr, DynamicArray* dst)
{
    uint srcCount = *(uint*)(thisPtr + 0x19c);
    if (srcCount < 2) {
        if (srcCount != 0) {
            // Process the single source item directly
            int* srcItem = **(int**)(thisPtr + 0x198);
            processItem(srcItem + 0x14); // offset 0x50 -> +0x14 from int*? Actually srcItem is int*, so +0x14 gives +0x50 bytes
        }
        return;
    }

    // Random starting index
    uint startIdx = (uint)_rand() % srcCount;
    uint idx;
    int* srcList = *(int**)(thisPtr + 0x198); // array of pointers

    // First loop: from startIdx to end
    for (idx = startIdx; idx < srcCount; idx++) {
        int* srcItem = *(int**)(srcList + idx);
        int capacity = dst->capacity;
        if (dst->size == capacity) {
            // Double capacity (or set to 1 if zero)
            int newCap = (capacity == 0) ? 1 : capacity * 2;
            reallocateDynamicArray(newCap); // This function should update dst internally
        }
        // Copy 12 bytes from srcItem+0x50 to dst's data buffer
        byte* dest = dst->data + dst->size * 12;
        dst->size++;
        if (dest != nullptr) {
            *(uint64*)dest = *(uint64*)(srcItem + 0x14);     // offset 0x50 = +0x14 from int* (since int is 4 bytes, +0x14 gives 80 bytes? Wait: int* +0x14 = +0x50 bytes? Actually int* has element size 4, so +0x14 means +0x50 bytes. Yes)
            *(uint32*)(dest + 8) = *(uint32*)(srcItem + 0x16); // offset 0x58 = +0x16 from int* (0x58-0x50=8)
        }
    }

    // Second loop: from 0 to startIdx-1
    if (startIdx != 0) {
        for (idx = 0; idx < startIdx; idx++) {
            int* srcItem = *(int**)(srcList + idx);
            int capacity = dst->capacity;
            if (dst->size == capacity) {
                int newCap = (capacity == 0) ? 1 : capacity * 2;
                reallocateDynamicArray(newCap);
            }
            byte* dest = dst->data + dst->size * 12;
            dst->size++;
            if (dest != nullptr) {
                *(uint64*)dest = *(uint64*)(srcItem + 0x14);
                *(uint32*)(dest + 8) = *(uint32*)(srcItem + 0x16);
            }
        }
    }
}
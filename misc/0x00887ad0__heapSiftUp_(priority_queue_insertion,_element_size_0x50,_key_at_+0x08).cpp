// FUNC_NAME: heapSiftUp (priority queue insertion, element size 0x50, key at +0x08)
// Function address: 0x00887ad0
// Sifts a new element up in a max-heap stored at param_1 (element size 0x50).
// param_2 = root index (usually 0), param_3 = initial hole index (the target insertion position),
// param_4 = pointer to the new element to insert.
// The key compared is at offset +0x08 of each element (uint32 priority/score).
void heapSiftUp(int heapBase, int rootIndex, int holeIndex, undefined4* newElement)
{
    // Heap element size = 0x50 bytes (20 dwords)
    #define HEAP_ELEMENT_SIZE 0x50
    #define KEY_OFFSET 0x08  // offset of uint32 key within element

    int parentIndex;
    undefined4* src;
    undefined4* dst;

    if (rootIndex < holeIndex) {
        do {
            parentIndex = (holeIndex - 1) >> 1;  // Parent in a 0-indexed binary heap
            // Break if new element's key <= parent's key (max-heap condition)
            if ((uint)newElement[2] <= *(uint*)(heapBase + parentIndex * HEAP_ELEMENT_SIZE + KEY_OFFSET))
                break;

            // Move parent element down to the hole
            src = (undefined4*)(heapBase + parentIndex * HEAP_ELEMENT_SIZE);
            dst = (undefined4*)(heapBase + holeIndex * HEAP_ELEMENT_SIZE);
            for (int count = 0x14; count != 0; count--) {  // 0x14 dwords = 0x50 bytes
                *dst = *src;
                src++;
                dst++;
            }

            holeIndex = parentIndex;
        } while (rootIndex < parentIndex);
    }

    // Copy new element into final hole position
    dst = (undefined4*)(heapBase + holeIndex * HEAP_ELEMENT_SIZE);
    for (int count = 0x14; count != 0; count--) {
        *dst = *newElement;
        newElement++;
        dst++;
    }
}
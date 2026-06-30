// FUN_004bb690: ArrayContainer::appendElements
// Address: 0x004bb690 - Function that appends a batch of elements (each 0x34 bytes) from a source array into a dynamic array, handling reallocation and ownership transfer of pointer fields at offsets +0xC, +0x18, +0x24 relative to element start.

void __thiscall ArrayContainer::appendElements(int* sourceBatch) {
    int* dst;
    int* src;
    uint i;
    uint numElements;

    numElements = 0;
    i = 0;

    // sourceBatch[0] = pointer to source array
    // sourceBatch[1] = number of elements to append
    if (sourceBatch[1] != 0) {
        do {
            // Check if capacity is reached; if so, double capacity (or set to 1)
            if (*(int*)(this + 0x8) == *(int*)(this + 0xC)) {
                int newCapacity = *(int*)(this + 0xC);
                if (newCapacity == 0) {
                    newCapacity = 1;
                } else {
                    newCapacity *= 2;
                }
                FUN_004bca00(newCapacity); // realloc internal array
            }

            // Calculate destination pointer: base + elementSize (0x34) * currentCount
            dst = (int*)(*(int*)(this + 0x8) * 0x34 + *(int*)(this + 0x4));
            // Increment element count
            *(int*)(this + 0x8) = *(int*)(this + 0x8) + 1;

            if (dst != (int*)0x0) {
                src = (int*)(sourceBatch[0] + numElements * 0x34); // source element base
                // Copy first 3 ints (0x0, 0x4, 0x8)
                dst[0] = src[0];
                dst[1] = src[1];
                dst[2] = src[2];
                // Release pointer fields at offsets +0xC, +0x18, +0x24 in source
                FUN_00498500(src + 3);  // source[3] likely pointer to release
                FUN_00498500(src + 6);  // source[6]
                FUN_00498500(src + 9);  // source[9]
                // Copy the 12th int (offset 0x30) - possibly a size or flags
                dst[0xC] = src[0xC];
            }
            numElements++;
        } while (numElements < (uint)sourceBatch[1]);
    }
    return;
}
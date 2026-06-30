// FUNC_NAME: RepackBlockData
// Purpose: Reorganizes blocks of data based on format ID. For format 0xD (13), applies a specific 4-to-6 element expansion pattern.
// Allocates output buffer, copies/remaps data, then frees input? (free call after copy)
// param1: formatId - data format identifier
// param2: elementCount - number of source elements
// param3: srcData - source data pointer
// param4: elementSize - size of each element in bytes
void RepackBlockData(int formatId, uint elementCount, void *srcData, size_t elementSize)
{
    void *dest;
    void *allocPtr;

    if (formatId == 0xD) { // Special format 13
        if (elementCount != 4) {
            uint blockCount = elementCount >> 2; // Groups of 4 source elements
            // Allocate 6 output elements per group, each of 4 bytes? (size params: 4, blockCount*6, flags)
            dest = alloc(4, blockCount * 6, 0, 1, 0);
            if (dest == nullptr) {
                return;
            }
            for (; blockCount != 0; blockCount--) {
                // Copy first element
                memcpy(dest, srcData, elementSize);
                // Copy second element
                memcpy((char*)dest + elementSize, (char*)srcData + elementSize, elementSize);
                void *srcThird = (char*)srcData + elementSize * 2;
                // Advance dest by 2 elements
                dest = (char*)dest + elementSize * 2;
                // Copy third element
                memcpy(dest, srcThird, elementSize);
                dest = (char*)dest + elementSize;
                // Copy first element again
                memcpy(dest, srcData, elementSize);
                dest = (char*)dest + elementSize;
                // Copy third element again
                memcpy(dest, srcThird, elementSize);
                dest = (char*)dest + elementSize;
                // Copy fourth element
                memcpy(dest, (char*)srcData + elementSize * 3, elementSize);
                dest = (char*)dest + elementSize;
                // Advance source by 4 elements
                srcData = (char*)srcData + elementSize * 4;
            }
            free(); // Release allocated buffer? (FUN_0060cde0)
            return;
        }
        // When elementCount == 4, treat as format 6 fallthrough
        formatId = 6;
    }
    // Generic path: allocate and copy directly
    dest = alloc(formatId, elementCount, 0, 1, 0);
    if (dest == nullptr) {
        return;
    }
    memcpy(dest, srcData, elementCount * elementSize);
    free();
}
// FUNC_NAME: copyIndexedElementsReversed
// Function at 0x004cd910: Copies elements from a source array to a destination buffer,
// using an index array in reverse order. Each source element is 6 bytes (three 16-bit values).
// The source descriptor structure contains count, source array pointer, and index array pointer.
// The destination buffer is passed in EDX (in_EAX in decompiler).
// This is likely a helper for reordering or gathering data (e.g., vertex indices, animation data).

void __fastcall copyIndexedElementsReversed(int srcDesc, int dstBuffer)
{
    int count;
    int srcBase;
    int *indexArray;
    int i;
    int srcOffset;
    unsigned short index;
    unsigned short *dstPtr;
    unsigned short *srcPtr;
    unsigned short *idxPtr;

    // Read count from source descriptor at offset 0x0C
    count = *(int *)(srcDesc + 0x0C) - 1;
    if (count >= 0)
    {
        // Source base pointer at offset 0x10
        srcBase = *(int *)(srcDesc + 0x10);
        // Index array pointer at offset 0x18 (array of ints, each low 16 bits is index)
        indexArray = *(int **)(srcDesc + 0x18);
        // Start writing at dstBuffer + 4? Actually dstPtr starts at dstBuffer+4, but writes go to dstBuffer, dstBuffer+2, dstBuffer+4
        dstPtr = (unsigned short *)(dstBuffer + 4);
        // Start reading indices from the last element (count * 4 bytes offset)
        idxPtr = (unsigned short *)((int)indexArray + count * 4);
        do
        {
            // Read index (low 16 bits of the int)
            index = *idxPtr;
            // Calculate source offset: each element is 6 bytes
            srcOffset = srcBase + (unsigned int)index * 6;
            // Copy three 16-bit values from source to destination
            // Write to dstBuffer + offset (dstPtr[-2] = dstBuffer, dstPtr[-1] = dstBuffer+2, dstPtr[0] = dstBuffer+4)
            dstPtr[-2] = *(unsigned short *)(srcOffset);
            dstPtr[-1] = *(unsigned short *)(srcOffset + 2);
            *dstPtr = *(unsigned short *)(srcOffset + 4);
            // Move destination pointer forward by 3 shorts (6 bytes)
            dstPtr += 3;
            // Move index pointer backward by 2 bytes (since ushort* decrement by 2)
            idxPtr -= 2;
            count--;
        } while (count >= 0);
    }
    return;
}
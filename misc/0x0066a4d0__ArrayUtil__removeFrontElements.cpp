// FUNC_NAME: ArrayUtil::removeFrontElements
void __fastcall ArrayUtil::removeFrontElements(void* unused, int* arrayHeader, int count)
{
    // arrayHeader points to a dynamic array structure:
    // +0x00: size (number of elements)
    // +0x04: capacity (max elements)
    // +0x08: unknown (set to 0 here)
    // +0x0C: data pointer to array of ints

    if (count > 0) {
        int currentSize = *arrayHeader; // size at +0x00
        if (currentSize <= count) {
            // Removing all elements - reset
            arrayHeader[2] = 0; // +0x08
            *arrayHeader = 0;   // size = 0
            memset((void*)arrayHeader[3], 0, arrayHeader[1] * 4); // clear entire data array
            return;
        }

        int* dataPtr = (int*)arrayHeader[3]; // +0x0C
        int copied = 0;
        int* src = dataPtr + count; // source starts after removed range
        if (currentSize != count && currentSize - count > 0) {
            do {
                *dataPtr = *src;  // shift elements left
                copied++;
                dataPtr++;
                src++;
            } while (copied < currentSize - count);
        }
        // Zero out the now-unused tail
        if (copied < currentSize) {
            do {
                *dataPtr = 0;
                copied++;
                dataPtr++;
            } while (copied < currentSize);
        }
        // Update size
        *arrayHeader = currentSize - count;
    }
}
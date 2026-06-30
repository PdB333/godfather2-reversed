// FUNC_NAME: Memory::fillArrayStrided
void __thiscall fillArrayStrided(size_t elementSize, void* dest, int count, size_t fillSize, unsigned char fillByte) 
{
    // Common helper for initializing arrays with a stride.
    // If elementSize == fillSize, write the entire block at once.
    // Otherwise, write fillSize bytes at each stride of elementSize.

    if (elementSize != fillSize) {
        // Strided fill: each element receives fillSize bytes, then pointer advances by elementSize.
        while (count != 0) {
            memset(dest, fillByte, fillSize);
            dest = (void*)((int)dest + elementSize);  // stride
            count--;
        }
    } else {
        // Contiguous fill: all elements are packed tightly.
        memset(dest, fillByte, elementSize * count);
    }
}
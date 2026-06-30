// FUNC_NAME: Buffer::ensureOwnedAndResize
void __thiscall Buffer::ensureOwnedAndResize(void)
{
    int newSize;
    uint computedSize;
    uint stackArg = 0; // output from FUN_0064b9e0
    
    // Compute desired new size using a helper function, initial hint 10
    FUN_0064b9e0(10, &stackArg);
    computedSize = stackArg & 0x3ff; // Mask to 10 bits (max 1023)
    
    // If we do not own the buffer (flag at +0x14 is 0), make a private copy
    if (*(char *)(this + 0x14) == '\0') {
        void* newBuf = malloc(*(size_t *)(this + 0x10)); // allocate same size as current
        memcpy(newBuf, *(void **)(this + 0xc), *(size_t *)(this + 0x10)); // copy data
        *(void **)(this + 0xc) = newBuf; // update pointer
        *(char *)(this + 0x14) = 1; // set ownership flag
    }
    
    // Resize if needed: if current capacity < computed new size, and we own the buffer, realloc
    if (*(uint *)(this + 0x10) < computedSize) {
        if (*(char *)(this + 0x14) != '\0') {
            *(uint *)(this + 0x10) = computedSize; // update capacity
            void* reallocBuf = realloc(*(void **)(this + 0xc), computedSize);
            *(void **)(this + 0xc) = reallocBuf;
        }
    } else {
        // Current capacity is already sufficient, just update size/capacity (or maybe store the desired size)
        *(uint *)(this + 0x10) = computedSize;
    }
    
    // Call helper to possibly fill or adjust the buffer (e.g., clear/init) with computedSize * 8 bytes?
    FUN_0064b9e0(computedSize * 8, *(undefined4 *)(this + 0xc));
    
    return;
}
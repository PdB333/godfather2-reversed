// FUNC_NAME: Buffer::shiftAndCopyElements
int Buffer::shiftAndCopyElements(int count) {
    // Offsets:
    // +0x14: pointer to a sub-structure (controlBlock)
    // +0x2e: short flag (maybe "ready" or "locked")
    // +0x08: source pointer (read from here)
    // +0x0c: destination pointer (write here)
    // Elements are 8 bytes each.

    int *controlBlock = *(int **)(this + 0x14);   // +0x14
    int sourcePtr = *(int *)(this + 0x08);        // +0x08
    int destPtr;

    if (*(short *)(this + 0x2e) != 0) {          // +0x2e: maybe flag like "active"
        flushInternal();                          // FUN_00633920
        // After flush, controlBlock might have been updated
        // extraout_EDX becomes the new controlBlock pointer? We'll use the original.
        // Actually the compiler might have used extraout_EDX, but we treat controlBlock as unchanged.
    }

    // Check if controlBlock has a "dirty" flag (bit 0)
    if ((*(byte *)(controlBlock + 8) & 1) != 0) {
        // Check another structure at controlBlock - 0x10 for a similar flag
        if ((*(byte *)(controlBlock - 0x10) & 1) != 0) {
            flushInternal();
            // Again, controlBlock might be updated; we keep original.
        }

        // Check if there's enough space at destination to accommodate 'count' elements
        // source + count * (-8) => source - 8*count
        int newDestPtr = *(int *)(this + 0x08) + count * (-8);
        if (*(unsigned int *)(this + 0x0c) < (unsigned int)newDestPtr) {
            // Copy elements from (source - 8*count) to destination
            int i = 0;
            if (count > 0) {
                int src = *(int *)(this + 0x08) + count * (-8);
                int *dest = (int *)(*(int *)(this + 0x0c) + i * 8);
                do {
                    dest[0] = *(int *)(src);
                    dest[1] = *(int *)(src + 4);
                    i++;
                    src += 8;
                } while (i < count);
            }
            // Update source pointer to after the copied block: destination + count*8
            *(int *)(this + 0x08) = *(int *)(this + 0x0c) + count * 8;
        }
    }

    // Set bit 4 (0x10) in controlBlock's offset 8 to mark modification
    *(unsigned int *)(controlBlock + 8) |= 0x10;
    return -1;
}
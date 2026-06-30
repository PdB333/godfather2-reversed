// FUNC_NAME: BufferPair::releaseBuffers
void __thiscall BufferPair::releaseBuffers(void* this, void* memoryManager) {
    int* counterPtr;
    byte firstSizeByte;
    int secondSize;

    // Offset +0x7: size of first buffer (as byte, likely power-of-two exponent)
    firstSizeByte = *(byte*)((int)this + 7);
    if (firstSizeByte != 0) {
        // Offset +0x10: pointer to first buffer
        if (*(int*)((int)this + 0x10) != 0) {
            // Free the first buffer using global deallocation function
            (*gDeallocFunc)(*(int*)((int)this + 0x10));
            if (memoryManager != 0) {
                // memoryManager + 0x10 points to a structure with a counter at +0x24
                counterPtr = (int*)(*(int*)((int)memoryManager + 0x10) + 0x24);
                // Subtract 0x14 * (2^(firstSizeByte & 0x1f)) from the counter
                *counterPtr = *counterPtr - (0x14 << (firstSizeByte & 0x1f));
            }
        }
    }

    // Offset +0x1c: size of second buffer (as int)
    secondSize = *(int*)((int)this + 0x1c);
    // Offset +0xc: pointer to second buffer
    if (*(int*)((int)this + 0xc) != 0) {
        // Free the second buffer
        (*gDeallocFunc)(*(int*)((int)this + 0xc));
        if (memoryManager != 0) {
            counterPtr = (int*)(*(int*)((int)memoryManager + 0x10) + 0x24);
            // Subtract secondSize * 8 from the counter
            *counterPtr = *counterPtr - (secondSize * 8);
        }
    }

    // Final deallocation (no argument) – likely a global cleanup or pool release
    (*gDeallocFunc)();
    if (memoryManager != 0) {
        counterPtr = (int*)(*(int*)((int)memoryManager + 0x10) + 0x24);
        // Always subtract 0x20 (32 bytes) from the counter
        *counterPtr = *counterPtr - 0x20;
    }
}
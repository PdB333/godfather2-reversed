// FUN_00647820: MemoryManager::allocateZeroed
unsigned int* __thiscall MemoryManager::allocateZeroed(int flags, int elementSize) {
    // Count is passed via EAX (register convention). This is an internal allocation helper.
    int count; // from eax
    unsigned int* dst = (unsigned int*)this->allocateRaw(flags, count * elementSize);
    if (dst != nullptr) {
        unsigned int header = dst[-1];
        unsigned int blockSize = header & 0x7ffffff8; // mask out flags, keep size aligned to 8
        if ((header & 2) == 0) { // bit 1 clear: block not pre-zeroed
            unsigned int payloadSize = blockSize - 4; // exclude header word
            if (payloadSize > 0x20) {
                memset(dst, 0, payloadSize);
            } else {
                // Inline zeroing for small blocks (payload <= 32 bytes)
                unsigned int* ptr = dst; // default pointer for direct cases
                switch (blockSize) {
                case 0x20: // total block size 32 -> payload 28 bytes (7 dwords)
                    *dst = 0;
                    dst[1] = 0;
                    ptr = dst + 2;
                case 0x18: // block 24 -> payload 20 bytes (5 dwords)
                    *ptr = 0;
                    ptr[1] = 0;
                    ptr = ptr + 2;
                case 0x10: // block 16 -> payload 12 bytes (3 dwords)
                    *ptr = 0;
                    ptr[1] = 0;
                    ptr = ptr + 2;
                case 0x8:  // block 8 -> payload 4 bytes (1 dword)
                    *ptr = 0;
                }
            }
        }
    }
    return dst;
}
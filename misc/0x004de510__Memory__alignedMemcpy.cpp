// FUNC_NAME: Memory::alignedMemcpy
void __thiscall Memory::alignedMemcpy(void* dst, const void* src, uint size)
{
    uint dstAlign;
    uint i;
    
    // Align destination to 64 bytes (cache line size)
    dstAlign = (uint)dst & 0x3f;
    while (dstAlign != 0 && size != 0) {
        *(uint32_t*)dst = *(uint32_t*)src;
        *((uint32_t*)dst + 1) = *((uint32_t*)src + 1);
        *((uint32_t*)dst + 2) = *((uint32_t*)src + 2);
        *((uint32_t*)dst + 3) = *((uint32_t*)src + 3);
        dst = (uint32_t*)dst + 4;
        src = (uint32_t*)src + 4;
        size -= 0x10;
        dstAlign = (uint)dst & 0x3f;
    }
    
    // Copy 64-byte blocks (cache line sized) for aligned destination
    if (0x40 < size) {
        i = ((size - 0x41) >> 6) + 1;
        do {
            // Copy 64 bytes (16 dwords) per iteration
            *(uint32_t*)dst = *(uint32_t*)src;
            *((uint32_t*)dst + 1) = *((uint32_t*)src + 1);
            *((uint32_t*)dst + 2) = *((uint32_t*)src + 2);
            *((uint32_t*)dst + 3) = *((uint32_t*)src + 3);
            *((uint32_t*)dst + 4) = *((uint32_t*)src + 4);
            *((uint32_t*)dst + 5) = *((uint32_t*)src + 5);
            *((uint32_t*)dst + 6) = *((uint32_t*)src + 6);
            *((uint32_t*)dst + 7) = *((uint32_t*)src + 7);
            *((uint32_t*)dst + 8) = *((uint32_t*)src + 8);
            *((uint32_t*)dst + 9) = *((uint32_t*)src + 9);
            *((uint32_t*)dst + 10) = *((uint32_t*)src + 10);
            *((uint32_t*)dst + 11) = *((uint32_t*)src + 11);
            *((uint32_t*)dst + 12) = *((uint32_t*)src + 12);
            *((uint32_t*)dst + 13) = *((uint32_t*)src + 13);
            *((uint32_t*)dst + 14) = *((uint32_t*)src + 14);
            *((uint32_t*)dst + 15) = *((uint32_t*)src + 15);
            src = (uint32_t*)src + 16;
            dst = (uint32_t*)dst + 16;
            size -= 0x40;
            i--;
        } while (i != 0);
    }
    
    // Copy remaining bytes
    while (size != 0) {
        *(uint32_t*)dst = *(uint32_t*)src;
        *((uint32_t*)dst + 1) = *((uint32_t*)src + 1);
        *((uint32_t*)dst + 2) = *((uint32_t*)src + 2);
        *((uint32_t*)dst + 3) = *((uint32_t*)src + 3);
        src = (uint32_t*)src + 4;
        dst = (uint32_t*)dst + 4;
        size -= 0x10;
    }
}
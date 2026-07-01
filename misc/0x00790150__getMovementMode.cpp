// FUNC_NAME: getMovementMode
unsigned char __thiscall getMovementMode(void* thisPtr) {
    // Offset +0x5c holds a flags word (uint32)
    unsigned int flags = *(unsigned int*)((char*)thisPtr + 0x5c);
    
    // Check bits: bit4 (0x10) -> return 3 (e.g., running), bit3 (0x08) -> return 2 (e.g., walking), else 1 (idle)
    if ((flags >> 4) & 1) {
        return 3;
    }
    if ((flags >> 3) & 1) {
        return 2;
    }
    return 1;
}
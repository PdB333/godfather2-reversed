// FUNC_NAME: writePacketInit (likely part of a packet builder/stream writer)
void __thiscall writePacketInit(void *this, bool flag) {
    // this+0x8 is a pointer to the current write position in the buffer
    int32_t *writePos = *(int32_t **)((uint8_t *)this + 8);
    
    // Write packet type identifier (always 1 in this context)
    *writePos = 1;
    
    // Write flag: true/false converted to uint32 (0 or 1)
    writePos[1] = (uint32_t)(flag != 0);
    
    // Advance write position by 8 bytes (two 32-bit words)
    *(int32_t *)((uint8_t *)this + 8) += 8;
}
// FUNC_NAME: IdBitSet::create
uint32_t* IdBitSet::create(uint32_t uiBitCount)
{
    uint32_t* pArray;
    uint8_t* pBuffer;
    
    // Allocate the IdBitSet structure (6 DWORDs = 24 bytes)
    pArray = (uint32_t*)FUN_00673070(); // likely pool allocation
    *pArray = (uint32_t)this;             // +0x00: store 'this' (or owner pointer) from implicit register
    pArray[1] = 0xFFFFFFFF;              // +0x04: free list head sentinel
    pArray[2] = 0xFFFFFFFF;              // +0x08: free list tail sentinel
    
    // Clamp bit count to maximum pool size (2048 bits)
    if (uiBitCount > 0x800) {
        uiBitCount = 0x800;
    }
    
    // Total buffer size = 2 * ceil(uiBitCount / 8) bytes (double buffer for frame flip)
    pArray[3] = ((uiBitCount + 7) >> 3) * 2; // +0x0C: total byte size
    
    // Allocate the double buffer
    pBuffer = (uint8_t*)FUN_00673070(); // pool allocator
    pArray[4] = (uint32_t)pBuffer;      // +0x10: start of buffer
    
    // Store pointer to the midpoint of the buffer (second half)
    pArray[5] = (uint32_t)(pBuffer + (pArray[3] >> 1)); // +0x14: second half start
    
    return pArray;
}
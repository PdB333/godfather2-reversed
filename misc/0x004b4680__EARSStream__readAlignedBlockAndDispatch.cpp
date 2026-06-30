// FUNC_NAME: EARSStream::readAlignedBlockAndDispatch
void __thiscall EARSStream::readAlignedBlockAndDispatch(void *pHandler) 
{
    // +0x18: current read pointer (pointer to pointer to data)
    uint32_t firstDword = **(uint32_t **)(this + 0x18);
    uint8_t *alignedPtr = (uint8_t *)(((uint32_t)*(uint32_t **)(this + 0x18) + 7) & ~3U);
    *(uint8_t **)(this + 0x18) = alignedPtr;

    uint8_t buffer[0x5c]; // 92 bytes
    _memcpy(buffer, alignedPtr, 0x5c);
    *(int *)(this + 0x18) = (int)alignedPtr + 0x5c; // advance by block size

    // Copy buffer to stack (may be for alignment or later usage)
    uint8_t stackBuffer[0x5c];
    for (int i = 0; i < 23; i++) { // 23 * 4 = 0x5c
        ((uint32_t *)stackBuffer)[i] = ((uint32_t *)buffer)[i];
    }

    // Call handler with the first dword (likely type/ID)
    (*(void (**)(uint32_t))pHandler)(firstDword);
}
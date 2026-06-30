// FUNC_NAME: StreamCipher::xorCrypt

void __thiscall StreamCipher::xorCrypt(StreamCipher* this, const uint8_t* src, uint8_t* dst, int32_t count)
{
    uint32_t stateWork[0x81]; // 0x81 * 4 = 0x204 bytes
    uint8_t* cipherState = (uint8_t*)((uintptr_t)this + 0x5c); // state table start
    int32_t* indexPtr = (int32_t*)((uintptr_t)this + 0x270); // current index into state

    // Copy state work area from offset 0x6c to local buffer (size 0x81 dwords)
    // This is used for the periodic rekey step.
    __movsd((uint32_t*)stateWork, (uint32_t*)((uintptr_t)this + 0x6c), 0x81);

    while (count > 0)
    {
        if (*indexPtr == 0x10) // every 16 bytes, rekey/update the state
        {
            // params: destination state, source state (self), work buffer
            FUN_00661210(cipherState, cipherState, stateWork);
            *indexPtr = 0;
        }

        uint8_t keyByte = cipherState[*indexPtr]; // get current key from state
        *dst = *src ^ keyByte;                    // XOR with source byte

        // Update state by storing the plain byte (like RC4 swap? But here it's just store)
        cipherState[*indexPtr] = *src;

        (*indexPtr)++;
        src++;
        dst++;
        count--;
    }
}
// FUNC_NAME: RandomBuffer::fillRandomChunks
void __thiscall RandomBuffer::fillRandomChunks(void* thisPtr, int chunkCount)
{
    // thisPtr is the 'this' pointer (ECX)
    // chunkCount is the number of 4-byte chunks to fill

    // Check if buffer is initialized (flag at offset 0xC)
    if (*(int*)((int)thisPtr + 0xC) == 0)
    {
        // Attempt to initialize the random buffer
        if (FUN_006385a0() != 0)  // some initialization check
        {
            FUN_00641890();        // perform initialization
            return;
        }
    }
    else if (chunkCount != 0)
    {
        // Buffer is initialized, fill random data
        // The random data starts at this+3 (likely an offset to a byte array)
        unsigned char* buffer = (unsigned char*)((int)thisPtr + 3);
        for (int i = 0; i < chunkCount; i++)
        {
            // Write 4 random bytes in reverse order (big-endian style)
            unsigned char* ptr = buffer + 3; // start at end of 4-byte chunk
            for (int j = 0; j < 4; j++)
            {
                *ptr = FUN_006418b0();  // get a pseudo-random byte
                ptr--;
            }
            buffer += 4; // move to next chunk
        }
    }
    return;
}
// FUNC_NAME: swap80ByteBlocks
// Address: 0x00888b20
// Role: Swaps two 80-byte (20 uint32) data blocks. Likely used to exchange controller slot states or packet buffers.
void swap80ByteBlocks(uint32_t* blockA, uint32_t* blockB)
{
    uint32_t temp[20]; // Temporary buffer for swap

    // Copy blockA to temp
    for (int i = 0; i < 20; ++i)
        temp[i] = blockA[i];

    // Copy blockB to blockA
    for (int i = 0; i < 20; ++i)
        blockA[i] = blockB[i];

    // Copy temp to blockB
    for (int i = 0; i < 20; ++i)
        blockB[i] = temp[i];
}
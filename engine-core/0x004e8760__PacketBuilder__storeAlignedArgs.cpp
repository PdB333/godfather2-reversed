// FUNC_NAME: PacketBuilder::storeAlignedArgs
void PacketBuilder::storeAlignedArgs(uint32_t headerValue, const __m128* data1, const __m128* data2, const __m128* data3, const __m128* data4)
{
    // Write the 4-byte header value at the current buffer position
    *(uint32_t*)(*(uint32_t*)(this + 0x14)) = headerValue; // +0x14: current write pointer (pointer to buffer)

    // Align the buffer pointer to 16 bytes (SSE alignment)
    uint8_t* alignedPtr = (uint8_t*)((*(uint32_t*)(this + 0x14) + 0x13) & 0xFFFFFFF0);
    *(uint32_t*)(this + 0x14) = (uint32_t)alignedPtr;

    // Copy four 16-byte aligned data blocks
    *(__m128*)alignedPtr = *data1;
    *(__m128*)(alignedPtr + 16) = *data2;
    *(__m128*)(alignedPtr + 32) = *data3;
    *(__m128*)(alignedPtr + 48) = *data4;

    // Advance the buffer pointer past the written data
    *(uint32_t*)(this + 0x14) += 0x10; // +0x10 = 16 bytes (one block)
}
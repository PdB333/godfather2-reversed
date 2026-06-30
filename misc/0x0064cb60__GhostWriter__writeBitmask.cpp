// FUNC_NAME: GhostWriter::writeBitmask
void __fastcall GhostWriter::writeBitmask(void* this, uint32_t flags, uint32_t destStream)
{
    // +0x18: bit count (number of dirty fields in the bitmask)
    uint32_t bitCount = *(uint32_t*)((uint8_t*)this + 0x18);
    // Convert bit count to byte count (round up)
    uint32_t byteCount = (bitCount + 7) >> 3;
    // +0x138: pointer to the packed bitmask array
    uint8_t* bitBuffer = (uint8_t*)this + 0x138;
    // Write the bitmask to the destination stream (likely a network packet or replay buffer)
    FUN_00658230(destStream, bitBuffer, byteCount, flags);
}
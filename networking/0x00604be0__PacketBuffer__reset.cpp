// FUNC_NAME: PacketBuffer::reset
PacketBuffer* __fastcall PacketBuffer::reset(PacketBuffer* thisPtr)
{
    // Offset 0x00: first 4-byte field (e.g., size/count)
    thisPtr->field_0 = 0;
    // Clear the remaining 0x1010 bytes (total struct size = 0x1014)
    memset(reinterpret_cast<char*>(thisPtr) + 4, 0, 0x1010);
    return thisPtr;
}
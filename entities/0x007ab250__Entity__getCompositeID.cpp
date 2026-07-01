// FUNC_NAME: Entity::getCompositeID
uint32 __thiscall Entity::getCompositeID(void)
{
    // this+0x58: pointer to a data block (e.g., behavior or shared data)
    uint32* dataBlock = *(uint32**)((char*)this + 0x58);
    // Read low byte from large offset in data block (e.g., a hash table or index array)
    uint8 lowByte = *(uint8*)((char*)dataBlock + 0x24F0);
    // Extract high 24 bits of the pointer itself (likely used as a type or group identifier)
    uint32 highPart = (uint32)dataBlock >> 8;
    // Combine: high 24 bits from pointer, low 8 bits from table
    return (highPart << 8) | lowByte;
}
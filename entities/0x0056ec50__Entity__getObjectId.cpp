// FUNC_NAME: Entity::getObjectId
uint32 Entity::getObjectId() const
{
    // +0x04: entity type byte (e.g., object category)
    uint8 entityType = *(uint8*)(this + 0x04);

    // +0x20: primary object ID (for types 0-9)
    // +0x28: secondary object ID (for types > 9)
    // Both stored as 32-bit values; mask to 28 bits (0xFFFFFFF) to extract actual ID
    if (entityType > 9)
    {
        return *(uint32*)(this + 0x28) & 0xFFFFFFF;
    }
    else
    {
        return *(uint32*)(this + 0x20) & 0xFFFFFFF;
    }
}
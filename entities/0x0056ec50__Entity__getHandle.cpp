// FUNC_NAME: Entity::getHandle
uint Entity::getHandle() const
{
    // Check the object type byte at offset +0x04
    // If type > 9, use the handle at +0x28, otherwise use the one at +0x20
    // Both handles are masked to 28 bits (lower 28 bits)
    if (9 < (*(uint *)(this + 4) & 0xff)) {
        return *(uint *)(this + 0x28) & 0xfffffff;
    }
    return *(uint *)(this + 0x20) & 0xfffffff;
}
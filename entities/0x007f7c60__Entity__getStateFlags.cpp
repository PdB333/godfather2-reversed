// FUNC_NAME: Entity::getStateFlags
uint __thiscall Entity::getStateFlags(Entity *this)
{
    // Read a 32-bit flags field at offset +0x8e0, shift right by 4, then mask to keep
    // bit 0 (original bit 4) and bits 8-31 (original bits 12-31) of the shifted value.
    // This extracts specific sub-flags from the state bitfield.
    return (*(uint *)((uint)this + 0x8e0) >> 4) & 0xffffff01;
}
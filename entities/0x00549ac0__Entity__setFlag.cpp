// FUNC_NAME: Entity::setFlag
// Address: 0x00549ac0
// Sets a byte flag in a nested substructure accessed via this+0x18 at offset +0x11.
void __thiscall Entity::setFlag(uint8_t flag)
{
    // Dereference pointer at this+0x18, then write flag to its +0x11 byte.
    *(uint8_t*)(*(int*)((uint8_t*)this + 0x18) + 0x11) = flag;
}
// FUNC_NAME: Entity::setFlag
// Address: 0x00549ab0
// Sets a byte flag at offset 0x10 of a sub-object pointed to by this+0x18.
// This pattern is common in EA EARS for simple state/flag setting.

void __thiscall Entity::setFlag(Entity* this, uint8_t value)
{
    // this+0x18 -> pointer to a sub-struct (likely m_pSubObject)
    // sub-struct+0x10 -> byte field (likely m_flags or m_state)
    *(uint8_t*)(*(int*)((uint8_t*)this + 0x18) + 0x10) = value;
}
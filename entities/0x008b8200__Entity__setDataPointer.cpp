// FUNC_NAME: Entity::setDataPointer
// Address: 0x008b8200
// Identified role: Simple setter for a pointer/data member at offset +0x10.
// Likely stores a generic data pointer or handle (e.g., user data, resource reference).

void __thiscall Entity::setDataPointer(void *value)
{
    this->m_pData = value;  // +0x10: pointer to game-specific data or handle
}
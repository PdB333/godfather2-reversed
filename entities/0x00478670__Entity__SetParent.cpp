// FUNC_NAME: Entity::SetParent
// Address: 0x00478670
// Role: Simple setter for the m_pParent field at offset +0x68.
void __thiscall Entity::SetParent(void *this, void *parent)
{
    *(void **)((int)this + 0x68) = parent; // +0x68: m_pParent (pointer to parent entity)
    return;
}
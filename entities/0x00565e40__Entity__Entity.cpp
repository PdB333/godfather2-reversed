// FUNC_NAME: Entity::Entity
void __thiscall Entity::Entity(int this, int initialOwner)
{
    EntityBase::EntityBase();  // base class constructor at 0x00adbf50
    *(int*)(this + 0xC) = initialOwner;  // +0xC: m_pOwner
    *(int*)(this + 0x38) = 1;            // +0x38: m_bActive flag
}
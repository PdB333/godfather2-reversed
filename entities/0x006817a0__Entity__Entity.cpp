// FUNC_NAME: Entity::Entity
// Function address: 0x006817a0
// Role: Constructor for Entity class, initializes base and sets field at +0x20 to 0

void __fastcall Entity::Entity(Entity *this)
{
    // Call base class constructor (likely EARSObject or similar)
    FUN_006809b0();
    
    // Initialize field at offset 0x20 to null/zero (e.g., m_pParent, m_flags, or m_pNext)
    *(int *)((char *)this + 0x20) = 0;
}
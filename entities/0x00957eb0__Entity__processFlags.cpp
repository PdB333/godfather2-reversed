// FUNC_NAME: Entity::processFlags
// Function address: 0x00957eb0
// Role: Checks two byte flags; if first is set, clears it and if second is also set, invokes a virtual method at vtable+0xA4.
// Offsets: 
//   +0x48 (byte) - flag2 (m_bFlag2)
//   +0x4C (byte) - flag1 (m_bFlag1)
// Virtual call at vtable offset 0xA4 (index 41) - likely a behavior update or state transition.

void __thiscall Entity::processFlags()
{
    if (this->m_bFlag1) {
        this->m_bFlag1 = false;
        if (this->m_bFlag2) {
            (this->*reinterpret_cast<void (Entity::*)()>(this->vtable[0xA4]))();
        }
    }
}
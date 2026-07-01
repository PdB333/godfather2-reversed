// FUNC_NAME: Entity::deinitializeState
void __thiscall Entity::deinitializeState(Entity* this)
{
    // Check if low byte of m_flags (+0x48) is zero (i.e., not already active/deactivated)
    if (*(char*)&this->m_flags == '\0') {
        // Reset counters at offsets 0x54, 0x58, 0x5C
        this->m_counter1 = 0;
        this->m_counter2 = 0;
        this->m_counter3 = 0;
        // Clear state byte at offset 0x50
        this->m_state = 0;
        // Get virtual function at vtable+0x28 (index 10)
        void (*onDeactivate)(Entity*) = this->vtable[0x28 / 4];
        // Mark as initialized (byte at offset 0x51)
        this->m_initialized = 1;
        // Call the virtual method (likely derived class cleanup)
        onDeactivate(this);
    }
}
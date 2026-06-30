// FUNC_NAME: PlayerActionable::requestCoverTransition
void __thiscall PlayerActionable::requestCoverTransition(PlayerActionable* this) {
    // Check if the cover transition has already been requested (bit 21 of m_flags) 
    // and if a global/manager flag (bit 30 at offset 0x1b94 of the object at +0x58) is clear.
    if (((this->m_flags >> 0x15) & 1) == 0 &&  // m_flags offset +0xa8
        ((*(uint32_t*)(*(int*)((uint8_t*)this + 0x58) + 0x1b94) >> 0x1e) & 1) == 0) {
        // Call the transition function on the object at +0xf4 (likely a state machine or component)
        FUN_007ee2e0((uint8_t*)this + 0xf4);
        // Mark the transition as requested
        this->m_flags |= 0x200000;
    }
}
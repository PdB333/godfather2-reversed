// FUNC_NAME: Entity::processPendingAction
undefined4 __fastcall Entity::processPendingAction(Entity* this) {
    // Check if bit 2 (0x4) is set in the flags at offset +0x6F4
    if ((this->m_flags & 0x0004) != 0) {
        // Call the function at vtable offset +0x94 of the object pointed to by m_pActionHandler (offset +0x2EC)
        (this->m_pActionHandler->vtable->handleAction)(this->m_pActionHandler);
        // Clear bit 2 in the flags
        this->m_flags &= ~0x0004;
    }
    return 0;
}
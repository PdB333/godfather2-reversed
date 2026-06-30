// FUNC_NAME: ActionStateMachine::updateState
undefined4 __thiscall ActionStateMachine::updateState(void) {
    uint flags = this->m_flags; // +0x34: state flags bitfield
    if ((flags >> 5) & 1) {
        return this->m_stateResult; // +0x3c: cached result
    }
    this->m_flags = flags | 0x20;

    int iVar1 = this->m_pConfig->someState; // +0x10 -> +0xd4: pointer to config object, offset 0xd4
    // Note: bit0 indicates "pending step"
    if (iVar1 != 0 && (flags & 1) == 0) {
        this->m_flags |= 1;
    }
    if (flags & 1) {
        // Step logic: if iVar1==0, clear pending and reset timer, also set flag3 if flag2 was set
        if (iVar1 == 0) {
            this->m_flags &= ~1;
            this->m_timer = 0.0f; // +0x38
            if (this->m_flags & 2) {
                this->m_flags |= 8;
            }
        }
    }

    // Compare values from config and target objects
    if (this->m_pConfig->someInteger == this->m_pTarget->otherInteger) { // +0x10->0x40, +0x14->0x54
        this->m_flags |= 4;
    } else if ((this->m_flags & 1) == 0) {
        // If not in pending step, advance timer
        this->m_timer = g_fDeltaTime + this->m_timer; // DAT_012067e8: global delta time
        if (g_fTimerThreshold < this->m_timer) { // _DAT_00e50db0: timer threshold
            this->m_timer = 0.0f;
            FUN_006bf3d0(); // Timer expiry callback
        }
    }

    undefined4 result = FUN_006bef70(); // Obtain current state value
    this->m_stateResult = result;
    FUN_006bec70(result); // Apply state value
    this->m_flags &= ~0x20;
    return result;
}
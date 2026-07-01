// FUNC_NAME: Player::canPerformAction
bool __thiscall Player::canPerformAction(bool defaultResult) {
    // Virtual function call at vtable+0x19c, likely checks if the entity is alive or valid
    if (!this->isAlive()) {
        return false;
    }

    // Check if a state field (offset +0xAA4) equals a global constant and a flag (bit 1) is set in a sub-object (pointer at +0x360, flags at offset +0x110)
    if ((this->m_state == g_someGlobalState) && ((this->m_pSubObj->flags >> 1) & 1)) {
        // Call to external function FUN_0055d790, likely returns a count (e.g., number of crew members)
        int count = getCrewCount();
        return count < 3;
    }

    return defaultResult;
}
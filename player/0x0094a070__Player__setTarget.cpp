// FUNC_NAME: Player::setTarget
void __thiscall Player::setTarget(int targetIndex, bool bNotify) {
    // +0x1A4: m_targetIndex (int)
    // +0x1A8: m_targetPointer (int*)
    // +0x11C: m_flags (uint) - bit 22 (0x400000) = hasTarget, bit 26 (0x4000000) = targetNotified
    this->m_targetIndex = targetIndex;
    this->m_targetPointer = g_targetArrayBase + targetIndex; // DAT_01205224 is base of target array
    this->m_flags |= 0x400000; // set hasTarget flag

    if (bNotify && ((this->m_flags >> 0x1A) & 1) == 0) {
        notifyTargetChanged(); // FUN_00949800 - global notification function
        this->m_targetPointer = nullptr;
        this->m_flags |= 0x4000000; // set targetNotified flag
    }
}
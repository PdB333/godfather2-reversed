// FUNC_NAME: PlayerSM::processUpdate
void __fastcall PlayerSM::processUpdate(PlayerSM* thisPtr) {
    // Check if the state machine is active (bit 0 of m_flags at +0x5c)
    if ((thisPtr->m_flags & 1) == 0) {
        // Not active, perform the actual update
        PlayerSM::doUpdate();
    }
    // If active, do nothing (skip update)
}
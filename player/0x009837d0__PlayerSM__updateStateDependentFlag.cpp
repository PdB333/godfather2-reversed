// FUNC_NAME: PlayerSM::updateStateDependentFlag
void __fastcall PlayerSM::updateStateDependentFlag(CPlayerSM* this)
{
    char newFlag = 0;

    // Check if the control flag (e.g., is something allowed) is set at +0x105
    if (this->field_0x105 != 0) {
        // Evaluate state at +0x5c: active if state is 0,1, or 4? Actually: if state < 2 or state == 4 => false, else true
        if ((this->m_currentState < 2) || (this->m_currentState == 4)) {
            newFlag = 0;
        } else {
            newFlag = 1;
        }
    }

    // If the actual flag (+0x104) differs from the computed one, update and call appropriate routine
    if (this->m_activeFlag != newFlag) {
        if (newFlag != 0) {
            // Start the associated behaviour (e.g., enable feature)
            FUN_006913c0();  // Likely start some engine subsystem
            this->m_activeFlag = newFlag;
            return;
        }
        // Stop the behaviour with parameter 10 (e.g., fade out)
        FUN_006915c0(10);
        this->m_activeFlag = 0;
    }
}
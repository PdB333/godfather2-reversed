// FUNC_NAME: FSM::setState

void __thiscall FSM::setState(int newStateArg)
{
    // Call state-change callback if registered (+0x58)
    if (this->m_pStateChangeCallback != nullptr) {
        this->m_pStateChangeCallback(newStateArg);
    }

    // Notify global manager (e.g., g_pStateManager) via vtable+0xc
    if (g_pSomeManager != nullptr) {
        g_pSomeManager->vtable->Notify();
    }

    // Deactivate current state if it exists (+0x0C)
    if (this->m_pCurrentState != nullptr) {
        // Call virtual function at offset 4 (deactivate)
        this->m_pCurrentState->deactivate(this);
        this->m_pCurrentState = nullptr;
    }

    // Store new state data
    this->m_stateArg = newStateArg;      // +0x18
    this->m_bStateDirty = 1;             // +0x14 (byte)
    this->m_stateId = 9;                 // +0x10
}
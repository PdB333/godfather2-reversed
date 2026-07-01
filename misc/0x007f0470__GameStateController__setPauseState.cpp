// FUNC_NAME: GameStateController::setPauseState
void __thiscall GameStateController::setPauseState(bool bPaused)
{
    // Offset 0x5E1, 0x5E3: Inverted pause flags
    this->m_bFlag1 = !bPaused;
    this->m_bFlag2 = !bPaused;

    // Global timestamp/handle used for synchronization
    DWORD dwCurrent = g_dwPauseTimestamp;
    this->m_dwValue1 = dwCurrent;
    this->m_dwValue2 = dwCurrent;
}
// FUNC_NAME: TimerManager::checkAndReset
int __thiscall TimerManager::checkAndReset(void)
{
    // +0x08 m_counter (uint)
    // +0x0C m_flag (int)
    // +0x10 m_pData (pointer, first byte treated as bool)
    if ((m_flag == 0) && (m_counter < s_globalTimeThreshold)) {
        FUN_005a04a0(m_pData, 0, 0, 0);   // unknown initialization call
        *(byte *)m_pData = 0;             // clear active flag at m_pData[0]
        m_counter = 0;
        m_flag = 0;
        return 2;                         // signal: timer expired and reset
    }
    return 0;                             // not ready or already active
}
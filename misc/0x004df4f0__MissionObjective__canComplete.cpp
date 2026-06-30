// FUNC_NAME: MissionObjective::canComplete

void MissionObjective::canComplete(void)
{
    // Fields at offsets:
    // +0x00: m_pPrereq1
    // +0x04: m_pPrereq2
    // +0x08: m_pPrereq3
    // +0x0C: m_pPrereq4
    // If all are null, objective is automatically completable.
    // Otherwise, check a global state to determine.

    bool allNull = (m_pPrereq1 == 0) && (m_pPrereq2 == 0) && (m_pPrereq3 == 0) && (m_pPrereq4 == 0);
    if (allNull)
    {
        // All prerequisites null: directly complete.
        FUN_0051a9f0();
        return;
    }

    // Some prerequisites exist; check current game state.
    int* statePtr = (int*)FUN_004e0f60();   // Get pointer to current state data
    int stateValue = 0;
    if (statePtr != nullptr)
    {
        stateValue = *statePtr;
    }

    if (stateValue != 0)
    {
        // State is non-zero, meaning condition satisfied.
        FUN_0051a9f0();
    }
    // else condition not satisfied, do nothing.
    return;
}
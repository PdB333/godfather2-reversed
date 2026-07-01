// FUNC_NAME: PlayerGroundSM::onStateExit
void __thiscall PlayerGroundSM::onStateExit(void)
{
    int thisPtr = (int)this;
    int currentState = *(int *)(thisPtr + 0x88); // +0x88: m_currentState (state ID)
    // 0x48 = STATE_NONE or STATE_INVALID; skip if already cleared
    if (currentState != 0 && currentState != 0x48)
    {
        int *manager = (int *)GetStateExitManager(); // FUN_008d9990 - global manager
        if (manager != (int *)0x0)
        {
            // Call virtual function at offset 0x7c (likely OnStateExit)
            (**(code **)(*manager + 0x7c))();
            NotifyStateExit(); // FUN_008d9640 - post-exit notification
        }
        // Clear a flag in the associated character/sentient object
        int *pCharacter = *(int **)(thisPtr + 0x58); // +0x58: m_pCharacter
        if (pCharacter != (int *)0x0)
        {
            uint *flags = (uint *)(pCharacter + 0x24a4); // +0x24a4: m_flags
            *flags = *flags & 0xfffffeff; // Clear bit 0x100 (e.g., kInStateFlag)
        }
        // Mark state as no longer active
        *(byte *)(thisPtr + 0x7d) = 0; // +0x7d: m_stateActiveFlag
    }
}

// Forward declarations of helper functions
extern int *GetStateExitManager(void); // FUN_008d9990
extern void NotifyStateExit(void);     // FUN_008d9640
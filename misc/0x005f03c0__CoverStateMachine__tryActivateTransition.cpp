// FUNC_NAME: CoverStateMachine::tryActivateTransition
// Address: 0x005f03c0
// Role: Attempt to activate a cover state transition by setting a flag, validating with a global manager,
//       and if a target is ready, finalizing the transition.

// Offset map for CoverStateMachine:
// +0x08: m_bTransitionFlag (bool/byte)
// +0x10: m_pTarget (CoverTarget*)

// Offset map for CoverTarget:
// +0x0C: m_bReady (bool/byte)

int __thiscall CoverStateMachine::tryActivateTransition(void)
{
    // Null check on 'this'
    if (this == nullptr)
    {
        return 0;
    }

    // Base preparation before transition
    basePrepare();                                         // FUN_005f2590

    // Set transition flag
    this->m_bTransitionFlag = 1;                           // +0x08

    // Validate activation using global manager
    bool canActivate = validateActivation(g_simManager, this); // FUN_005e51a0

    if (canActivate)
    {
        // Perform pre-transition logic
        onTransitionStart();                               // FUN_005f3770

        CoverTarget* target = this->m_pTarget;             // +0x10
        if ((target != nullptr) && (target->m_bReady != 0)) // target->+0x0C
        {
            // Clear ready flag and transition flag
            target->m_bReady = 0;                          // target->+0x0C
            this->m_bTransitionFlag = 0;                   // +0x08

            // Cleanup and finalize transition
            onTransitionCleanup();                         // FUN_005f57b0
            onTransitionComplete();                        // FUN_005f0420

            return 1;
        }
    }
    return 0;
}
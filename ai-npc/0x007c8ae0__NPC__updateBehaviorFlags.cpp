// FUNC_NAME: NPC::updateBehaviorFlags

void __thiscall NPC::updateBehaviorFlags(void)
{
    uint flags = this->m_flags;
    // Clear bit 0x400 (bit 10) — used as a "needs update" flag.
    flags &= 0xFFFFFBFF;
    this->m_flags = flags;

    // Check if the object is not currently active (bit 0 cleared means not processing)
    if ((flags & 0x1) == 0)
    {
        // Query the current behavior state from the controller at offset +0x58
        int state = FUN_007e56b0(this->m_pController); // EARS::AI::getCurrentState()
        if (state == 2) // e.g., kStateActionReady or kStateTransition
        {
            // Only trigger if cooldown flag (bit 12) is not set
            if ((flags & 0x1000) == 0)
            {
                FUN_007c7650(); // EARS::AI::executeAction()
            }
            // Set the "needs update" flag again
            this->m_flags |= 0x400;
        }
    }
    return;
}
// FUNC_NAME: PlayerStateMachine::setStateFlag

void __thiscall setStateFlag(bool enableFlag)
{
    uint flags = *(uint *)(this + 0xc88); // +0xC88: bitfield state flags

    if (!enableFlag)
    {
        // Clear bit 7 (0x80) – e.g., "active" or "enabled"
        flags &= ~0x80;
        *(uint *)(this + 0xc88) = flags;
        *(int *)(this + 0xc84) = 0; // +0xC84: state timer/counter reset
    }
    else
    {
        // Only allow setting bit 7 if bit 6 (0x40) is already set – e.g., "can transition"
        if (flags & 0x40)
        {
            flags |= 0x80;
            *(uint *)(this + 0xc88) = flags;
            *(int *)(this + 0xc84) = 0;
        }
    }

    // If bit 21 (0x200000) is set, trigger a state update/transition
    if (*(uint *)(this + 0xc88) & (1 << 21))
    {
        handleStateTransition(); // FUN_0087bd50 – likely a state handler
    }
}
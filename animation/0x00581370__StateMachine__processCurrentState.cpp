// FUNC_NAME: StateMachine::processCurrentState
void __thiscall StateMachine::processCurrentState(void)
{
    // +0x68: pointer to current state data (flags + timer)
    uint* pStateData = *(uint**)(this + 0x68);
    uint flags = *pStateData;

    if ((flags & 0x10) == 0)
    {
        // State not playing (0x10 clear)
        if ((flags & 0x20) != 0 && (short)pStateData[1] > 0)
        {
            // Transition requested and timer remaining (second word as short)
            if ((flags & 0x200) == 0)
            {
                int timer = *(int*)(this + 0x1C) + 1; // +0x1c: timer for normal transition
                FUN_00589450(0, timer, timer);
            }
            else
            {
                int timer = *(int*)(this + 0x0C) + 1; // +0x0c: timer for alternative transition
                FUN_00589360(0, timer, timer);
            }
        }
    }
    else
    {
        // State is playing (0x10 set)
        int timer = *(int*)(this + 0x24) + 1; // +0x24: timer for playing state
        FUN_00589a90(timer);
    }

    // Re-read flags (may have changed?)
    flags = *pStateData;

    if ((flags & 0x40) == 0)
    {
        if ((char)flags < 0) // bit 7 set
        {
            int timer = *(int*)(this + 0x44) + 1; // +0x44: timer for bit 7
            FUN_00589ef0(timer, timer);
        }
        else if ((flags & 0x100) == 0)
        {
            FUN_0058a290();
        }
        else
        {
            int timer = *(int*)(this + 0x34) + 1; // +0x34: timer for bit 8
            FUN_00589bf0(timer, timer);
        }
    }
    else
    {
        FUN_0058a1f0();
    }

    if ((*pStateData & 0x800) != 0)
    {
        int timer = *(int*)(this + 100) + 1; // +0x64: timer for bit 11
        FUN_0058a330(timer, timer);
    }

    // Advance state data pointer by 8 bytes (next state data element)
    *(int*)(this + 0x68) = (int)pStateData + 8;
}
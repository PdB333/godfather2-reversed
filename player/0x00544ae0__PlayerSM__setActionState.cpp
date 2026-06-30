// FUNC_NAME: PlayerSM::setActionState
void __thiscall PlayerSM::setActionState(int mode)
{
    // Virtual method at vtable+0x198: checks if state change is allowed (e.g., not playing critical animation)
    bool ready = (*(bool (__thiscall **)(void))(*(int *)this + 0x198))();
    // Pointer at this+0x360 is likely a component data block (e.g., m_pStateData)
    int* pStateData = *(int**)((char*)this + 0x360);
    // Offset +0x10c stores the current mode (param)
    if (!ready || *(int*)(pStateData + 0x10c) == mode)
        return;

    // Second pointer at pStateData+0x18 probably points to current state descriptor or animation state
    short* pAnimState = (short*)(*(int*)((char*)pStateData + 0x18) + 0x2a); // short at +0x2a: current movement/cover state

    if (mode == 1)
    {
        // State 1: enter cover or start a specific action
        if (*pAnimState != 6)
            *pAnimState = 6;
        FUN_0055d870(); // likely PlayCoverAnimation or EnableCoverBehavior
        *(int*)(pStateData + 0x10c) = 1;
        return;
    }

    // mode is not 1; default to state 3
    if (*pAnimState != 3)
        *pAnimState = 3;
    if (mode == 2)
    {
        FUN_0055d810(); // likely StopCoverAnimation or DisableCoverBehavior
    }
    *(int*)(pStateData + 0x10c) = mode;
}
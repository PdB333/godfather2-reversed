// FUNC_NAME: PlayerSM::processActionCheck
void __thiscall PlayerSM::processActionCheck(int thisPtr, int unusedParam, int param3)
{
    // Read state type identifier at +0xDC
    int stateType = *(int *)(thisPtr + 0xDC);
    
    // If stateType is 11 (0xB) or 12 (0xC), read a sub-state from a large offset
    if (stateType == 11)
    {
        stateType = *(int *)(thisPtr + 0x588);  // Sub-state for type 11
    }
    else if (stateType == 12)
    {
        stateType = *(int *)(thisPtr + 0x6E8);  // Sub-state for type 12
    }
    
    // Only proceed if the resulting state is 5 (e.g., "idle") or 7 (e.g., "moving")
    if (stateType != 5 && stateType != 7)
    {
        return;
    }
    
    // Get a manager object based on whether param3 is zero
    int *managerPtr = (int *)getActionManager(param3 == 0);
    
    // Call a virtual function at vtable offset 0x98 on the manager
    // This likely triggers an action or state change
    (*(void (**)(void))(*managerPtr + 0x98))();
}
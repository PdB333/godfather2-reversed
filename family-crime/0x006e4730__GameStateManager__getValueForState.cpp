// FUNC_NAME: GameStateManager::getValueForState
void __thiscall GameStateManager::getValueForState(int thisPtr, undefined4 param_2, int* outValue)
{
    int* piVar1;
    int stateMachinePtr;
    
    // Check if the object at +0x100 is valid
    if ((*(int*)(thisPtr + 0x100) != 0) &&
        (piVar1 = (int*)FUN_0043b870(DAT_01131018), piVar1 != (int*)0x0) &&
        (stateMachinePtr = (**(int (__thiscall**)(int*))*piVar1 + 0x34))(piVar1), stateMachinePtr != 0))
    {
        switch(*(int*)(stateMachinePtr + 0x38))
        {
        case 0:
            *outValue = 0;
            return;
        case 1:
            *outValue = _DAT_00d5780c;
            return;
        case 2:
            *outValue = DAT_00d5eee4;
            return;
        case 3:
            *outValue = DAT_00e445ac;
            return;
        case 4:
            *outValue = DAT_00d5ddec;
            return;
        case 5:
            *outValue = DAT_00d5779c;
            return;
        case 6:
            *outValue = DAT_00e44634;
            return;
        case 7:
            *outValue = DAT_00e445fc;
            return;
        case 8:
            *outValue = DAT_00e448a4;
            return;
        }
    }
    *outValue = 0;
    return;
}
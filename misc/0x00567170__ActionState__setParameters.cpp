// FUNC_NAME: ActionState::setParameters
void __thiscall ActionState::setParameters(int param)
{
    // +0x10: actionType (int) - set to 9 (likely an enum value)
    *(int *)(this + 0x10) = 9;
    // +0x14: stateFlag (byte) - set to 2 (possible sub-state or flag)
    *(char *)(this + 0x14) = 2;
    // +0x18: parameterValue (int) - stores the passed parameter
    *(int *)(this + 0x18) = param;
}
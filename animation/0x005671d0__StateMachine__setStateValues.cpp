// FUNC_NAME: StateMachine::setStateValues
void __thiscall StateMachine::setStateValues(int thisPtr, int stateId)
{
    *(int*)(thisPtr + 0x10) = 9;      // +0x10: stateType (e.g., enum StateType)
    *(char*)(thisPtr + 0x14) = 2;     // +0x14: subState (e.g., substate index)
    *(int*)(thisPtr + 0x18) = stateId; // +0x18: stateId (unique identifier)
}
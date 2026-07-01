// FUNC_NAME: StateMachine::setupTrackToPositionAndDirectionStateTable
void __thiscall StateMachine::setupTrackToPositionAndDirectionStateTable(int* this, undefined4 arg1, undefined4 arg2)
{
    // Check if the state table has already been initialized (hash 0x27a0f69c)
    if (isFlagSet(0x27a0f69c) == 0)
    {
        int vtablePtr = *this; // vtable pointer at offset 0x00
        undefined4 stateTableHandle = getStateTableByName("trackToPositionAndDirectionStateTable");
        // Call virtual function at vtable+0x20 (likely setStateTable or initialize)
        (*(code**)(vtablePtr + 0x20))(arg1, arg2, stateTableHandle);
        setFlag(1); // Mark as initialized
    }
    return;
}
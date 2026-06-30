// FUNC_NAME: StateMachineNode::setStateAndNotify
void __fastcall StateMachineNode::setStateAndNotify(int thisPtr)
{
    // thisPtr + 0x8: some identifier (e.g., node ID or argument)
    // thisPtr + 0xC: pointer to a function table (vtable-like)
    // thisPtr + 0x10: current state (set to 6, likely an enum value)
    // The function table at offset 0x34 is called with (arg, 1)
    int arg = *(int *)(thisPtr + 8);
    void (**funcTable)(int, int) = *(void (***)(int, int))(thisPtr + 0xC);
    // Call the function at offset 0x34 in the table
    funcTable[0x34 / 4](arg, 1);
    // Set state to 6 (e.g., kStateActive or kStateCompleted)
    *(int *)(thisPtr + 0x10) = 6;
}
// FUNC_NAME: GameStateMachine::setState
void __thiscall GameStateMachine::setState(int thisPtr, byte newStateValue)
{
    // Store the new state value in member at +0x14
    *(byte *)(thisPtr + 0x14) = newStateValue;
    // Update global current state value
    DAT_00f17964 = (uint)newStateValue;
    // Reset counter at +0x18
    *(undefined4 *)(thisPtr + 0x18) = 0;
    // Write global state value to some structure (DAT_012234d8 + 0xc)
    *(uint *)(DAT_012234d8 + 0xc) = DAT_00f17964;
    // Call update/process function
    FUN_005648c0();
    // Handle transition from state 1
    if (*(int *)(thisPtr + 0x10) == 1)
    {
        // Check global pointer and chain conditions
        if (((DAT_012233a0 != 0) && (**(int **)(DAT_012233a0 + 4) != 0)) &&
            (**(int **)(DAT_012233a0 + 4) != 0x1f30))
        {
            // Call handler with the state value
            FUN_00799220(*(undefined1 *)(thisPtr + 0x14));
        }
        // Call reset function with argument 0
        FUN_00444930(0);
    }
    // Advance state to 2 unless already 3
    if (*(int *)(thisPtr + 0x10) != 3)
    {
        *(undefined4 *)(thisPtr + 0x10) = 2;
    }
    return;
}
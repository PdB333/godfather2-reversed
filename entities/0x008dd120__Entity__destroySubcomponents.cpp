// FUNC_NAME: Entity::destroySubcomponents
void __fastcall Entity::destroySubcomponents(int thisPtr)
{
    int *vtablePtr;
    int secondHandle;

    // +0x194: handle to first sub-object (e.g., Animation)
    if (*(int *)(thisPtr + 0x194) != 0 && *(int *)(thisPtr + 0x194) != 0x48) {
        // Recover object pointer by subtracting header size (0x48)
        if (*(int *)(thisPtr + 0x194) == 0) {
            vtablePtr = (int *)0x0;
        }
        else {
            vtablePtr = (int *)(*(int *)(thisPtr + 0x194) + -0x48);
        }
        // Call virtual destructor/cleanup at vtable offset 0x70
        (*(code **)(*vtablePtr + 0x70))();
        // Free the sub-object memory (pool ID 0)
        FUN_007077a0(0);
        // +0x1bc: handle to second sub-object (e.g., Physics)
        secondHandle = *(int *)(thisPtr + 0x1bc);
        if (secondHandle != 0 && *(int *)(secondHandle + 8) != 0) {
            // Additional cleanup for the second sub-object
            FUN_009e7530(secondHandle);
        }
    }
    // +0x18c: handle to third sub-object (e.g., Sound)
    if (*(int *)(thisPtr + 0x18c) != 0 && *(int *)(thisPtr + 0x18c) != 0x48) {
        if (*(int *)(thisPtr + 0x18c) == 0) {
            vtablePtr = (int *)0x0;
        }
        else {
            vtablePtr = (int *)(*(int *)(thisPtr + 0x18c) + -0x48);
        }
        (*(code **)(*vtablePtr + 0x70))();
        if (*(int *)(thisPtr + 0x18c) != 0) {
            FUN_007077a0(0);
            return;
        }
        FUN_007077a0(0);
    }
}
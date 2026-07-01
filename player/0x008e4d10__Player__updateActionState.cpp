// FUNC_NAME: Player::updateActionState
undefined1 __thiscall Player::updateActionState(int thisPtr, undefined4 param2, undefined4 param3, undefined4 param4)
{
    char cVar1;
    int iVar2;

    // Call some initialization or pre-update function
    FUN_008e35f0();

    // Handle action counter at +0x1dc
    iVar2 = *(int *)(thisPtr + 0x1dc);
    if (iVar2 == -1) {
        *(undefined4 *)(thisPtr + 0x1dc) = 0;
    } else {
        *(int *)(thisPtr + 0x1dc) = iVar2 + 1;
        // Check if counter exceeds 2 or the corresponding action slot is empty
        if ((2 < iVar2 + 1) || (*(int *)((iVar2 + 0x10) * 0x20 + thisPtr) == 0)) {
            *(undefined4 *)(thisPtr + 0x1dc) = 0xffffffff; // -1
        }
    }

    // Set busy flag at +0x1a5
    *(undefined1 *)(thisPtr + 0x1a5) = 1;

    // Get some global object (e.g., game manager) and copy a value from it
    iVar2 = FUN_0078e110();
    if (iVar2 != 0) {
        *(undefined4 *)(thisPtr + 0x1a8) = *(undefined4 *)(iVar2 + 0x188);
    }

    // Process the action with the given parameters
    cVar1 = FUN_008e4be0(param2, param3, param4);
    if (cVar1 == '\0') {
        // If processing failed, call cleanup
        FUN_008e3cf0();
    }

    // Return the busy flag
    return *(undefined1 *)(thisPtr + 0x1a5);
}
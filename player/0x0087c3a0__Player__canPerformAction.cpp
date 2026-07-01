// FUNC_NAME: Player::canPerformAction
// Address: 0x0087c3a0
// Checks if the player can perform a specific action (param_2).
// Returns 1 if allowed, 0 if not.
// Conditions: not in certain state (flags bit 15), some virtual function returns >0,
// no pending action (field at +0xB74 == 0), helper function returns false,
// some virtual function result <= global threshold, another virtual returns true,
// and flags bit 11 not set.
// If param_2 is non-zero, also checks that no existing action of that type is in the action list.

bool __thiscall Player::canPerformAction(int *thisPtr, int actionType)
{
    char cVar1;
    int iVar2;
    int iVar3;
    float extraout_ST0;
    float extraout_ST0_00;
    int local_14[2]; // stack buffer for iteration
    int local_10;
    int local_c;

    // Check flags at offset 0x322 (0xC88) - bit 15 must be 0
    if (((((uint)thisPtr[0x322] >> 0xf & 1) == 0) &&
         // Virtual function at vtable+0xC0: returns something > 0
         ((**(code **)(*thisPtr + 0xc0))(), (float)0 < extraout_ST0)) &&
        // Field at offset 0x2dd (0xB74) must be 0 (no pending action?)
        (thisPtr[0x2dd] == 0) &&
        // Helper function FUN_0087ae60 must return false (0)
        (((cVar1 = FUN_0087ae60(), cVar1 == '\0' &&
          // Virtual function at vtable+0x1b0: result <= global threshold _DAT_00d76a90
          ((**(code **)(*thisPtr + 0x1b0))(), extraout_ST0_00 <= (float)_DAT_00d76a90)) &&
         // Virtual function at vtable+0x294 must return non-zero
         ((cVar1 = (**(code **)(*thisPtr + 0x294))(), cVar1 != '\0' &&
          // Flags bit 11 must be 0
          (((uint)thisPtr[0x322] >> 0xb & 1) == 0)))))) {
        // If actionType is specified, check if it's already in the action list
        if ((actionType != 0) && (iVar2 = FUN_0043b870(DAT_01130fa0), iVar2 != 0)) {
            local_c = 0;
            local_10 = 0;
            // Virtual function at vtable+0x1cc: get first element of action list
            (**(code **)(*thisPtr + 0x1cc))(&local_10);
            do {
                // Virtual function at vtable+500 (0x1f4): get current action ID
                iVar3 = (**(code **)(*thisPtr + 500))(local_14);
                if (((iVar3 != 0) && (iVar3 = FUN_0043b870(DAT_01131040), iVar3 != 0)) &&
                   (*(int *)(iVar3 + 0x24) == iVar2)) {
                    // Found matching action, cannot perform
                    return 0;
                }
                // Virtual function at vtable+0x1d0: move to next element
                cVar1 = (**(code **)(*thisPtr + 0x1d0))(&local_14, &local_14);
            } while (cVar1 != '\0');
        }
        return 1;
    }
    return 0;
}
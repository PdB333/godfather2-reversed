// FUNC_NAME: GameAction::tryExecute
// Address: 0x004ac480
// Role: Attempts to execute a game action with conditional checks based on object state and global conditions.

uint __thiscall GameAction::tryExecute(uint param2, uint param3, uint param4, uint param5, char param6, uint param7, uint param8, uint param9)
{
    char cVar1;
    uint uVar2;

    // Check if param6 is zero (meaning the action is allowed to proceed)
    // and if the target validation function succeeds
    if ((param6 == '\0') && (cVar1 = FUN_0045ef40(param2, param3), cVar1 != '\0'))
    {
        // Get the parent object pointer from this+0x48 (offset to parent)
        // If null, use 0; otherwise adjust by subtracting 0x48 (likely multiple inheritance offset)
        if (*(int *)(this + 0x48) == 0) {
            uVar2 = 0;
        }
        else {
            uVar2 = *(int *)(this + 0x48) - 0x48;
        }

        // Check condition pointer at uVar2+0x218
        // If NULL, or if non-NULL and global state check fails (FUN_00572530 returns false),
        // then early return with low byte cleared
        if ((*(int *)(uVar2 + 0x218) == 0) ||
            ((*(int *)(*(int *)(uVar2 + 0x218) + 0x124) != 0 &&
              (uVar2 = FUN_00572530(), (char)uVar2 == '\0'))))
        {
            return uVar2 & 0xffffff00;
        }
    }

    // Prepare context for the action
    FUN_00460340(param3, param9);
    // Execute the core action with all parameters
    uVar2 = FUN_0045f0c0(param2, param3, param4, param5, param7, param8, 1);
    return uVar2;
}
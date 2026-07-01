// FUNC_NAME: PlayerActionableInfo::onActionTrigger
undefined4 __thiscall PlayerActionableInfo::onActionTrigger(int *thisPtr, int actionId)
{
    char isAllowed;
    int currentActionId;

    isAllowed = FUN_008755d0(actionId);
    if (isAllowed != '\0')
    {
        currentActionId = (*(code **)(*thisPtr + 0x1e4))();
        if (currentActionId == actionId)
        {
            if (FUN_00542d70() != 0)  // Check if player is in appropriate state
            {
                FUN_0086d060(0, 1);   // Complete action animation or effect
            }
            (*(code **)(*thisPtr + 0x28c))(0);  // Clear action tracking
            thisPtr[0x3ca] = thisPtr[0x3ca] & 0xf1efffff;  // Clear action-related flags
        }
        return 1;
    }
    return 0;
}
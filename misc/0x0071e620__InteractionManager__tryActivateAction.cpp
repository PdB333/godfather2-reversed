// FUNC_NAME: InteractionManager::tryActivateAction
// Address: 0x0071e620
// Checks if a target object can accept an interaction and, if so, triggers the action.
// targetObj: non-null object with a vtable, must have a virtual method at +0x1C.
// Returns 1 on success, 0 on failure.

__thiscall int InteractionManager::tryActivateAction(int thisPtr, int* targetObj)
{
    char canActivate;

    if ((targetObj != nullptr) && (*(int*)(thisPtr + 0xC) != 0))
    {
        // Call virtual method at offset 0x1C on target's vtable
        // Typically "canInteract" or "isValidTarget", passing condition from this+0xC
        canActivate = (**(code**)(*targetObj + 0x1C))(*(int*)(thisPtr + 0xC));
        if (canActivate)
        {
            // Execute the action via callback with global data
            FUN_0071dfc0(targetObj, DAT_00d5ccf8);
            return 1;
        }
    }
    return 0;
}
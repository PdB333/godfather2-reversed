// FUNC_NAME: AIComponent::handleActionStateChange
void __fastcall AIComponent::handleActionStateChange(int thisPtr)
{
    int actionStatus;
    int actionId;

    // Check if there is a pending action pointer at offset 0xFC
    if (*(int *)(thisPtr + 0xfc) != 0) {
        actionStatus = FUN_006bf5d0();  // Gets the current action status (e.g., 2 = interrupted, 1 = success)
        if (actionStatus != 0) {
            // Determine which action ID to check based on status
            if (actionStatus == 2) {
                actionId = *(int *)(thisPtr + 0x40);  // Possibly "nextActionId" or "interruptedActionId"
            } else {
                actionId = *(int *)(thisPtr + 0x3c);  // Possibly "currentActionId"
            }
            // Compare actionId with a specific hash (likely a string hash for "COVER" or similar)
            if (actionId == 0x637b907) {
                // If matching, perform a global action, like clearing a cover state flag
                FUN_00402050(&DAT_0112a59c, 0);  // Sets some global variable to 0
            }
            // Notify other systems about the action completion
            FUN_008c5420(thisPtr, actionStatus);  // E.g., update animation state
            FUN_008c53a0(thisPtr, actionStatus);  // E.g., update AI state machine

            // If the pending action object still exists, call its virtual function at vtable+0x18 (likely a cleanup/virtual "complete" method)
            if (*(int **)(thisPtr + 0xfc) != (int *)0x0) {
                (**(code (***)(void))(**(int **)(thisPtr + 0xfc) + 0x18))(1);  // Call with arg 1 (possibly "immediate" flag)
            }
            // Clear the pending action pointer
            *(int *)(thisPtr + 0xfc) = 0;

            // Update a timestamp or state at offset 0x100 from a global object
            if (*(int *)(DAT_0112a668 + 0x18) != 0) {
                *(int *)(thisPtr + 0x100) = *(int *)(*(int *)(DAT_0112a668 + 0x18) + 0xbc);
            }
            // Call a finalization function (e.g., update global AI tick count)
            FUN_006b2f70();
        }
    }
}
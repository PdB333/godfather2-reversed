// FUNC_NAME: ActionQueue::processNextAction
// Address: 0x00691530
// Processes the next action from the global action stack. The stack stores pointers to action objects.
// Global state: gGameManager (0x012233b4) +0x565 holds the current action state ID.
// Actions are stored in gActionStack (0x00e50610) with gActionStackIndex (0x00e50650) as the top index.
// @param thisUnused: Ignored in the decompiled version (likely __thiscall with unused this)
// @param maxActions: Limit on number of concurrent actions (compared to 0xF)
void __thiscall ActionQueue::processNextAction(int thisUnused, int maxActions) {
    // Get current action state ID from global game manager
    char actionState = *(char*)(DAT_012233b4 + 0x565); // +0x565: mActionStateId (0x12 = idle?)

    // Only proceed if not idle, stack index is valid, and top entry is non-null
    if ((actionState != 0x12) && (DAT_00e50650 != -1) && ((&DAT_00e50610)[DAT_00e50650] != 0)) {
        // If maxActions limit is below 15 and not idle, perform initialization actions
        if ((maxActions < 0xf) && (actionState != 0x12)) {
            // Prepare vtable for the current action state
            FUN_00411070(actionState);
            // Additional work (e.g., frame setup)
            FUN_004958a0();
        }

        // Pop the top action from the stack (if stack still valid)
        if (DAT_00e50650 != -1) {
            int* poppedAction = (&DAT_00e50610)[DAT_00e50650]; // retrieve action pointer
            DAT_00e50650 = DAT_00e50650 - 1;                  // decrement stack index

            // Get vtable for the action type (based on current action state)
            int* vtable = (int*)FUN_00411070(actionState);
            // Call the virtual function at vtable offset +8 (likely execute/process)
            (**(code**)(*vtable + 8))(poppedAction);
        }
    }
}
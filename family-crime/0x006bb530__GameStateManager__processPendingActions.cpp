// FUNC_NAME: GameStateManager::processPendingActions
void __thiscall GameStateManager::processPendingActions(int *thisPtr)
{
    int *pThis;
    char isReady;
    unsigned int maxActions;
    unsigned int actionCount;
    undefined4 actionData;
    undefined4 iterator;  // uStack_8
    int someObject;       // local_4 (might be uninitialized but used later)

    pThis = thisPtr;
    if ((thisPtr != (int *)0x0) && (thisPtr[0x2e4] == 0)) {  // +0x2e4: busy flag
        // Get current timestamp or global state ID
        maxActions = FUN_00543330();  // e.g., get CurrentTick()
        // Virtual call: get number of actions to process (vtable offset 0x1fc)
        actionCount = (**(code **)(*pThis + 0x1fc))();
        if ((actionCount == maxActions) && 
            (isReady = FUN_006bb1a0(pThis + 8, &thisPtr, &iterator), isReady != '\0')) {
            // Iterate through all actions
            maxActions = 0;
            if (actionCount != 0) {
                do {
                    actionData = FUN_006bb160(thisPtr);  // Get next action data
                    FUN_00878030(actionData);             // Process/retain action
                    isReady = FUN_006bb240(iterator, &thisPtr);  // Advance iterator
                    if (isReady == '\0') break;
                    maxActions = maxActions + 1;
                } while (maxActions < actionCount);
            }
            FUN_00878980(iterator);  // Release iterator
            // Set state function pointer at offset 0x158 (0x56 * 4)
            pThis[0x56] = (int)&LAB_006bae20;  // Next processing step

            // Potential uninitialized local_4 usage; assume it's set by FUN_006bb1a0
            // or should be read from thisPtr. Based on pattern, probably
            // some additional cleanup.
            if (*(int *)(someObject + 0x1c) != 0) {
                FUN_005fde60(*(int *)(someObject + 0x1c) + 0x1c);
            }
            *(undefined4 *)(someObject + 0xc) = 0;
        }
    }
}
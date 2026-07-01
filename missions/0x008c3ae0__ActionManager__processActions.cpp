// FUNC_NAME: ActionManager::processActions
// Address: 0x008c3ae0
// Role: Iterates over pending actions and processes them if conditions are met.

void __fastcall ActionManager::processActions(int thisPtr)
{
    uint uIndex;
    int iState;
    int iData;
    char cCondition;
    int iStack0;

    uIndex = 0;
    if (*(int *)(thisPtr + 0x1a8) != 0) { // count of actions
        do {
            // Action item pointer from array at +0x1a4
            int* pAction = *(int**)(*(int*)(thisPtr + 0x1a4) + uIndex * 4);
            iState = *(int*)(pAction + 1); // offset +4: action state
            // Check state: not 0 (invalid) and not 7 (completed)
            if ((iState != 0) && (iState != 7)) {
                iData = *(int*)(pAction + 4); // offset +0x10: action data pointer
                if (iData != 0) {
                    // Condition check (e.g., phase/time validity)
                    cCondition = FUN_008fda60();
                    if (cCondition != '\0') {
                        // Queue or execute the action with its data
                        iStack0 = iData;
                        FUN_008c2290(&iStack0);
                    }
                }
            }
            uIndex = uIndex + 1;
        } while (uIndex < *(uint *)(thisPtr + 0x1a8));
    }
    return;
}
// FUNC_NAME: StreamManager::syncStreamState
// Function address: 0x00977cf0
// Role: Manages streaming state machine for asset loading with timeout (25s)
// This __thiscall function handles transitions between load states (3 and 4)
// based on external conditions and a timer.

int __thiscall StreamManager::syncStreamState(StreamManager* this, char bForce) {
    int iResult;
    int iTimer;

    // If there are items pending in queue (count > 0), return immediately (1 = in progress)
    if (*(int*)((char*)this + 0x138) > 0) {
        return 1;
    }

    iResult = getConditionFlag();  // FUN_00849ff0: returns 0 if condition OK, else non-zero

    if (bForce == 0) {
        // Normal path: check current state
        switch (*(int*)((char*)this + 0x14c)) {  // state field at +0x14c
        case 3: {  // Waiting for condition
            char bCondition = isConditionMet();  // FUN_004035a0: returns non-zero if condition true
            if (bCondition != 0 && iResult == 0) {
                // Condition met and no blocking: advance to state 4
                *(int*)((char*)this + 0x14c) = 4;
                int startTime = GetTickCount();  // FUN_00494d10
                *(int*)((char*)this + 0x154) = startTime;
                startLoadOperation();  // FUN_00977440
                return 0;  // In progress
            }
            break;
        }
        case 4: {  // Waiting for load completion with timeout
            int currentTime = GetTickCount();
            int savedTime = *(int*)((char*)this + 0x154);
            char bCondition = isConditionMet();
            if ((uint)(currentTime - savedTime) < 25000 && bCondition == 0) {
                // Timeout not reached and condition not met yet
                return 0;  // Still waiting
            }
            // Timeout or condition met: copy target value into current
            *(int*)((char*)this + 0x13c) = *(int*)((char*)this + 0x144);
            break;
        }
        }
        // Flowing through to reset if no return above
    } else {
        // Forced reset path
        if (*(int*)((char*)this + 0x13c) != *(int*)((char*)this + 0x144)) {
            // Values differ: start over from state 3
            *(int*)((char*)this + 0x14c) = 3;
            *(int*)((char*)this + 0x13c) = 0;
            startLoadOperation();  // FUN_00977440
            return 0;
        }
        // Fall through to LAB_00977dd5
    }

    // LAB_00977dd5: Reset and signal completion
    int iVal = getConditionFlag();
    *(int*)((char*)this + 0x13c) = iVal;
    *(int*)((char*)this + 0x140) = iVal;

    // If condition flag is 0 and a global object is valid, override +0x140 with its value
    if (iVal == 0) {
        Globals* pGlobals = *(Globals**)0x0112a66c;  // Global singleton pointer
        if (pGlobals != NULL && *(int*)((char*)pGlobals + 0x14) != 0) {
            void* pObj = *(void**)((char*)pGlobals + 0x10);
            if (pObj != NULL) {
                int** ppInt = *(int***)pObj;
                *(int*)((char*)this + 0x140) = *ppInt[0x50 / 4]; // Dereference offset 0x50
            }
        }
    }
    return 1;  // Operation complete
}

// Helper function declarations (unreferenced externs for clarity)
// static int getConditionFlag();          // FUN_00849ff0
// static char isConditionMet();           // FUN_004035a0
// static int GetTickCount();              // FUN_00494d10
// static void startLoadOperation();       // FUN_00977440
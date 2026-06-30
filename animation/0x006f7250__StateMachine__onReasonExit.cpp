// FUNC_NAME: StateMachine::onReasonExit
// Address: 0x006f7250
// Called from FUN_006f1440, likely part of StateMachine class.
// This function handles state exit events with different behaviors based on reason ID.
// Offsets: +0x14: m_pfnOnEvent, +0x18: m_pEventUserData, +0x24: m_ppStateFlag, +0x2c: m_state, +0x30: m_bExiting

void __thiscall StateMachine::onReasonExit(int thisPtr, uint argData, int reason)
{
    uint* pfnCallback;
    uint* pDefaultCallback;

    pfnCallback = (uint*)(thisPtr + 0x14); // +0x14
    if ((*(int*)(thisPtr + 0x14) != 0) && (*(code*)*pfnCallback != (code*)0x0)) {
        // Call the registered callback with event data
        (*(code*)*pfnCallback)(argData, reason, *(undefined4*)(thisPtr + 0x18)); // +0x18
    }

    switch(reason) {
    case 0: // StateExit_Completed
    case 3: // StateExit_Interrupted
    case 4: // StateExit_Cancelled
        // Clear exiting flag and current state
        *(byte*)(thisPtr + 0x30) = 0; // +0x30
        *(uint*)(thisPtr + 0x2c) = 0; // +0x2c

        // Get default callback pair (probably singleton)
        pDefaultCallback = (uint*)FUN_006fbc40(0, 0);
        if (pfnCallback != pDefaultCallback) {
            *pfnCallback = *pDefaultCallback;
            *(uint*)(thisPtr + 0x18) = pDefaultCallback[1];
        }
        FUN_006fbc70(); // Cleanup after callback swap

        // Clear external state flag if it exists
        if (*(undefined4**)(thisPtr + 0x24) != (undefined4*)0x0) { // +0x24
            **(undefined4**)(thisPtr + 0x24) = 0;
        }
        break;

    case 2: // StateExit_Failed probably
        // Set state to failure indicator
        *(uint*)(thisPtr + 0x2c) = 3;
        return;
    }

    return;
}
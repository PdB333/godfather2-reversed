// FUNC_NAME: PlayerSM::updateStateMachine
// Function address: 0x00566e90
// Identified as: Player state machine update; checks for subcomponent, reads global phase, and dispatches actions.

// Note: Based on offsets and patterns, this function appears to be a member of a state machine class.
// The subcomponent at +0x0C is likely an inner state handler.
// The global at DAT_012234d8 might be a game phase/switch manager.

void __thiscall PlayerSM::updateStateMachine(void)
{
    int iMode;
    undefined4 uRetVal;
    int iGlobalPhase;
    int iSomeData;
    undefined1 localStackBuf[1116]; // +0x45C

    // Check if the sub-component (inner state handler) is null
    if (*(int *)(this + 0x0C) == 0) {
        // No sub-component -> set default state flag and state ID
        *(undefined1 *)(this + 0x14) = 1;   // +0x14: state flag (ready?)
        *(undefined4 *)(this + 0x10) = 9;   // +0x10: current state ID (e.g., STATE_IDLE)
    }
    else {
        // Read global phase from well-known address
        iGlobalPhase = *(int *)(DAT_012234d8 + 4);
        if (iGlobalPhase != 5) {
            // Read data field at +0x11C (could be count, priority, or event type)
            iSomeData = *(int *)(this + 0x11C);
            // Compute mode: if iSomeData != 0 then mode = 0, else mode = 2
            iMode = (-(uint)(iSomeData != 0) & 0xFFFFFFFE) + 2;
            // Call virtual function at offset 0x4C (likely returns a descriptor or result)
            uRetVal = (*(code **)(*(int *)this + 0x4C))(iMode, iGlobalPhase, iSomeData);
            // Call debug/logging helper with same parameters
            FUN_00b11f00(uRetVal, iMode, iGlobalPhase, iSomeData);
            // Call virtual function at offset 0x18 on the sub-component,
            // passing a large stack buffer (likely for temporary state storage)
            (*(code **)(**(int **)(this + 0x0C) + 0x18))(localStackBuf);
            return;
        }
    }
    return;
}
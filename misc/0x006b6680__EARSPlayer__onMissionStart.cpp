// FUNC_NAME: EARSPlayer::onMissionStart
// Address: 0x006b6680
// This function appears to handle the start of a mission/level for a player entity.
// It checks state, sets flags, plays audio, and initializes movement/animation systems.

undefined1 __thiscall EARSPlayer::onMissionStart(int thisPtr, int param2, int param3, undefined4 param4, int *param5)
{
    uint *flagsPtr;
    int *intPtr;
    char result;
    int currentState;
    int nextState;
    undefined4 returnVal;
    float10 extraout_ST0;
    undefined4 localStack_3c;
    undefined ***stackPtr_38;
    undefined1 stackByte_34;
    undefined **stackPtr_30;
    int stackInt_2c;
    int stackInt_28;
    undefined4 stackVal_24;
    int *stackPtr_20;
    undefined1 localArr_1c [20];
    int aiStack_8 [2];
    
    result = FUN_006b4cd0(); // Likely some core validation or state check
    currentState = param2;
    if (result == '\0') {
        return 0;
    }
    returnVal = 0;
    if ((param5 != (int *)0x0) && (param2 == 0)) {
        param2 = 0;
        result = (**(code **)(*param5 + 0x10))(0x55859efa,&param2); // Runtime type check / cast
        if ((result != '\0') && (param2 != 0)) {
            currentState = *(int *)(param2 + 0x1ed4); // Get state from some large class (e.g. GameManager)
        }
    }
    if (*(int *)(thisPtr + 0xfc) != 0) {
        flagsPtr = (uint *)(*(int *)(thisPtr + 0xfc) + 0x34); // Assuming some sub-component at +0xFC with flags at +0x34
        *flagsPtr = *flagsPtr | 8; // Set flag bit 3
    }
    nextState = param3;
    if (param3 == 0) {
        nextState = thisPtr + 0x10; // Default to some object at offset 0x10 (maybe a component)
    }
    if (currentState == 0x637b907) { // 104362247 - Could be a state ID for "PLAYING" or "ACTIVE"
        returnVal = 1;
        FUN_007e7df0(0x1e); // Play sound effect (0x1E = 30)
        if ((*(int *)(thisPtr + 0xc4) == 1) && (*(int *)(thisPtr + 0xc0) != 0)) {
            currentState = FUN_0084a410(); // Get current game state / mission ID
            if (currentState != 0) {
                currentState = FUN_0084a410(); // Another state check
                if (currentState != 0x637b907) {
                    result = FUN_0084a670(); // Check if some condition is met
                    if (result != '\0') {
                        FUN_00894c90(0x4c498ac2); // Log or trigger event
                    }
                }
            }
        }
    }
    else if (*(int *)(thisPtr + 0x40) == 0x637b907) { // Check another state at +0x40
        FUN_007e7df0(0x1f); // Play sound effect (0x1F = 31)
    }
    FUN_006b4e30(4,0); // Reset some system (maybe input or state machine)
    FUN_006b65b0(); // Update some tracking or component
    FUN_006b2220(thisPtr + 0x84); // Clear/reset a timer or flag
    FUN_006b2220(thisPtr + 0x9c); // Clear/reset another timer or flag
    if (*(int *)(thisPtr + 0xd8) != 0) {
        currentState = FUN_0043b870(DAT_0112afb8); // Get some global entity
        if (currentState != 0) {
            FUN_0078b4b0(DAT_00d5e288,0,1); // Load/activate a resource (e.g. zone or stream)
        }
    }
    *(uint *)(thisPtr + 0x34) = *(uint *)(thisPtr + 0x34) | 0x2000000; // Set a large flag (bit 25)
    FUN_00892af0(0); // Clear some global state
    FUN_00892ab0(thisPtr,returnVal); // Notify observers or update state
    FUN_00894c40(0x2cc60947,localArr_1c); // Send a message/event with ID and data
    intPtr = param5;
    returnVal = param4;
    stackPtr_38 = &stackPtr_30;
    stackPtr_30 = &PTR_LAB_00d5e230; // Some vtable pointer for base class
    stackVal_24 = param4;
    stackPtr_20 = param5;
    localStack_3c = DAT_0112a5e0; // Another global pointer
    stackByte_34 = 0;
    stackInt_2c = thisPtr;
    stackInt_28 = nextState;
    FUN_00408a00(&localStack_3c,0); // Initialize/start some subsystem (e.g. movement controller)
    if (*(int *)(thisPtr + 0xd8) != 0) {
        (**(code **)(**(int **)(thisPtr + 0xd8) + 0xc0))(); // Call virtual function on component (+0xC0 = e.g. updateMovement)
        if ((float10)0 < extraout_ST0) {
            FUN_0046ffe0(nextState,0); // Set some animation state
            (**(code **)(**(int **)(thisPtr + 0xd8) + 0x288))(4,returnVal,intPtr); // Call another virtual (e.g. startTransition)
            FUN_0072d290(); // Update animation or physics
        }
    }
    *(uint *)(thisPtr + 0x34) = *(uint *)(thisPtr + 0x34) | 0x400000; // Set flag (bit 22)
    stackPtr_30 = &PTR_LAB_00e2f0c0; // Another vtable pointer
    if (aiStack_8[0] != 0) {
        FUN_004daf90(aiStack_8); // Cleanup / reference decrement
    }
    return 1;
}
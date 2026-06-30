// FUNC_NAME: StateMachine::processStateTransition
// Address: 0x0072e4a0
// Role: Handles state transitions for a state machine, checking conditions and performing setup/teardown.

void __thiscall StateMachine::processStateTransition(int* this, int* pTargetState) {
    char isValidState;
    int* pTemp;
    int iResult;
    int* pDonControlMgr;
    undefined4 uVar4;
    undefined4 uVar6;
    float fTransitionTime;
    undefined4 local_40;
    undefined*** local_3c;
    undefined1 local_38;
    undefined** local_24;
    int local_20[3];
    undefined8 local_14;
    undefined4 local_c;
    undefined1 local_8;
    undefined4 local_4;

    // Null check and ensure we are not transitioning to the current state
    if ((pTargetState != (int*)0x0) && (this != pTargetState)) {
        // Validate the target state
        isValidState = FUN_00715cd0(pTargetState, 0, 0);
        if (isValidState != '\0') {
            // Initialize local timer/event data
            local_c = 0;
            local_14 = 0;
            local_24 = &PTR_FUN_00d5dbbc; // vtable for some helper object?
            local_20[1] = 0;
            local_20[2] = 0;
            local_8 = 0;
            local_4 = DAT_01205228; // global constant
            local_20[0] = -0x84ee158; // negative constant (cleanup identifier)

            // Call target state's enter/method
            FUN_0044b210(pTargetState);

            // Get the global game manager pointer
            iResult = FUN_00471610();
            local_8 = 1;
            // Extract timer values from the manager
            local_14 = *(undefined8*)(iResult + 0x30);
            local_c = *(undefined4*)(iResult + 0x38);

            // Set up transition timer
            local_3c = &local_24;
            local_40 = DAT_0112ad8c; // another global
            local_38 = 0;
            if (this == (int*)0x0) {
                pTemp = (int*)0x0;
            } else {
                pTemp = this + 0xf; // offset to a member variable
            }
            FUN_00408bf0(&local_40, pTemp, 0); // set timer with this+0xf

            // Get transition time from a virtual method (vtable offset 0xBC)
            fTransitionTime = (float)(**(code**)(*this + 0xbc))(pTargetState);
            if (fTransitionTime == (float)0) {
                // No transition time => immediate state change, check special conditions
                pDonControlMgr = (int*)FUN_0043b870(DAT_01131018);
                if (pDonControlMgr != (int*)0x0) {
                    iResult = (**(code**)(*pDonControlMgr + 0x34))(); // virtual method, likely getCurrentState
                    if ((iResult != 0) && (*(int*)(iResult + 0x30) == 1)) {
                        // Check if there is a current gangster
                        if (*(int*)(iResult + 4) == 0) {
                            iResult = 0;
                        } else {
                            iResult = *(int*)(iResult + 4) + -0x48; // offset to gangster component
                        }
                        iResult = FUN_006bc8b0(iResult); // get gangster object
                        if ((iResult != 0) && ((*(byte*)(iResult + 0x44) & 0x80) != 0)) {
                            // Play audio event
                            uVar6 = 0;
                            uVar4 = FUN_006fbc40(0, 0);
                            FUN_007f96a0(0x9330ebf8, 0x75, uVar4, uVar6); // audio event hash
                            FUN_006fbc70();
                        }
                    }
                }
            }
            // Cleanup local timer/event if initialized
            if (local_20[0] != 0) {
                FUN_004daf90(local_20);
            }
        }
    }
    return;
}
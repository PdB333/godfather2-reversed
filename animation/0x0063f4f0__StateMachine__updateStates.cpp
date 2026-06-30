// FUNC_NAME: StateMachine::updateStates
void __thiscall StateMachine::updateStates(void) {
    int* managerObj = *(int**)(this + 0x1c);  // +0x1c: pointer to associated state manager (e.g., AI manager)
    FUN_0063f440();  // some initialization or idle processing

    int currentState = *(int*)(this + 0xc);  // +0xc: current state ID
    while ((unsigned int)(currentState - 0x28) < 0xf7) {  // valid state range [0x28, 0x11E)
        int expr = currentState - 0x28;
        bool callCommonStep = false;

        switch (expr) {
            case 0x28:   // corresponds to state 0x50
            case 0x7b:   // state 0xA3
            case 0x11e:  // state 0x146 (max in range?)
                FUN_00642ec0();   // common transition handler
                callCommonStep = true;
                break;

            case 0x2e:   // state 0x56
                FUN_0063e790(this);
                break;

            case 0x3a: {  // state 0x62
                *(int*)(this + 8) = *(int*)(this + 4);  // copy from +0x4 to +0x8
                if (*(int*)(this + 0x14) == 0x11f) {   // if previous state is sentinel (0x11f = 287)
                    *(int*)(this + 0xc) = FUN_00639c70(this + 0x10);  // compute next state via callback
                } else {
                    *(int*)(this + 0xc) = *(int*)(this + 0x14);  // restore previous state
                    *(int*)(this + 0x10) = *(int*)(this + 0x18);  // shift state stack
                    *(int*)(this + 0x14) = 0x11f;                 // reset previous state to sentinel
                }

                // Prepare locals for some debug/log call
                int local_18 = FUN_0063dd40();
                int local_1c = 4;
                int local_14 = 4;
                int local_8 = -1;
                int local_4 = -1;
                int local_10 = FUN_00642970(*(int*)(this + 0x1c), &local_1c);
                FUN_00643170(&local_14);

                callCommonStep = true;
                break;
            }

            case 0x5b: {  // state 0x83
                int* someStructPtr = (int*)FUN_00642b00();  // returns pointer to a struct
                if (someStructPtr[0] == 0xb) {
                    if (someStructPtr[3] != someStructPtr[4]) {
                        if (someStructPtr[1] < *(int*)(managerObj + 0x34)) {
                            // fall through to else path
                        } else {
                            FUN_00642d90(someStructPtr[1]);
                            // after call, skip the else (effectively goto end of if)
                        }
                    }
                } else {
                    FUN_00642ec0();  // common transition (unusual, but matches original)
                }

                FUN_0063e860();
                int newValue = FUN_00642fc0();
                someStructPtr[2] = newValue;
                someStructPtr[0] = 8;
                break;
            }

            default:
                return;  // exit if state not in handled set
        }

        // Common step for cases that need to advance state
        if (callCommonStep) {
            FUN_0063f300(this);  // state advancement / transition
        }

        // Refresh current state for loop condition
        currentState = *(int*)(this + 0xc);
    }
}
// FUNC_NAME: PlayerStateMachine::updateState
// Function address: 0x00566c90
// Role: State machine update logic, handles state transitions and animations
// Offset map:
// +0x10: int32 substate (0, 9, 10)
// +0x14: int8 state (1=idle?, 2=active?, 3=transitioning?, 4=exiting?)
// +0x2c: uint32 flags (bit9=forceTransition, bit10=exitPending, bit11=specialTransition)
// +0x18: void* callbackData
// +0x120: void (*callback)(void*)

#include <stdint.h>

class PlayerStateMachine {
public:
    // __thiscall
    void updateState();
};

void __thiscall PlayerStateMachine::updateState() {
    uint32 flags = *(uint32*)((uint8*)this + 0x2c);
    int8 state = *(int8*)((uint8*)this + 0x14);
    int32 substate = *(int32*)((uint8*)this + 0x10);

    // Check exit pending flag
    if ((flags >> 10) & 1) {
        exitCurrentState();   // FUN_00566af0
        *(uint32*)((uint8*)this + 0x2c) &= ~0x400;  // clear bit10
    }

    // Check force transition flag
    if ((flags >> 9) & 1) {
        enterNewState();      // FUN_00af3560
        exitCurrentState();   // FUN_00566af0 (redundant? order matters)
        *(uint32*)((uint8*)this + 0x2c) &= ~0x200;  // clear bit9
        finalizeStateTransition();  // FUN_00b02ab0
        return;
    }

    // State-based transitions
    if (state == 3) {
        enterNewState();      // FUN_00af3560
        *(int8*)((uint8*)this + 0x14) = 4;
        finalizeStateTransition();  // FUN_00b02ab0
        return;
    }

    if (state == 1 || state == 2) {
        updateActiveState();  // FUN_00566b70
    }
    else if (substate == 9) {
        // Check special transition flag
        if (!((flags >> 11) & 1)) {
            // No flag: go to state 2, reset substate
            *(int8*)((uint8*)this + 0x14) = 2;
            *(int32*)((uint8*)this + 0x10) = 0;
            finalizeStateTransition();  // FUN_00b02ab0
            return;
        }
        else {
            // Flag set: advance substate to 10, invoke callback
            *(int32*)((uint8*)this + 0x10) = 10;
            void (*callback)(void*) = *(void (**)(void*))((uint8*)this + 0x120);
            if (callback != nullptr) {
                void* callbackData = *(void**)((uint8*)this + 0x18);
                callback(callbackData);
                finalizeStateTransition();  // FUN_00b02ab0
                return;
            }
        }
    }

    // Default: finish transition if any
    finalizeStateTransition();  // FUN_00b02ab0
}
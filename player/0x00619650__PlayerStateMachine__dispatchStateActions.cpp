// FUNC_NAME: PlayerStateMachine::dispatchStateActions

// 0x00619650 - Dispatches actions based on the current state ID.
// This function is part of a state machine for player states.
// It reads the current state from m_currentState (+0x14), compares it to
// stored state constants, and handles each state appropriately.
// Some states delegate to helper functions, others return stored values.

int __fastcall PlayerStateMachine::dispatchStateActions(PlayerStateMachine* this) {
    int currentState = *(int*)((char*)this + 0x14); // m_currentState
    int result;

    // Preprocess state machine (e.g., update timers, check conditions)
    preprocessStateMachine(); // FUN_00612a60

    // Attempt to get default result from state parameters
    result = getDefaultStateActionResult(
        *(int*)((char*)this + 0x108),  // m_stateParamA
        *(int*)((char*)this + 0xe0)    // m_stateParamB
    ); // FUN_0060aa90

    // Dispatch based on current state ID
    if (currentState == *(int*)((char*)this + 0x114)) { // m_stateConstant1
        result = *(int*)((char*)this + 0xa4);           // m_stateResult1
        if (*(int*)((char*)this + 0xe4) != 0) {         // m_overrideFlag1
            result = getStateOverrideResult();           // FUN_006063b0
        }
    }
    else if (currentState == *(int*)((char*)this + 0x118)) { // m_stateConstant2
        result = *(int*)((char*)this + 0xa8);           // m_stateResult2
        if (*(int*)((char*)this + 0xe8) != 0) {         // m_overrideFlag2
            result = getStateOverrideResult();
        }
    }
    else {
        // All remaining states call processStateActionEffect with state-specific parameters
        if (currentState == *(int*)((char*)this + 0x11c)) { // m_stateConstant3
            result = processStateActionEffect(
                currentState,
                *(int*)((char*)this + 0xec),  // m_stateActionParamA3
                *(int*)((char*)this + 0xac)   // m_stateActionParamB3
            ); // FUN_0060b2f0
        }
        else if (currentState == *(int*)((char*)this + 0x128)) { // m_stateConstant4
            result = processStateActionEffect(
                currentState,
                *(int*)((char*)this + 0xf0),  // m_stateActionParamA4
                *(int*)((char*)this + 0xac)   // m_stateActionParamB4 (reused offset)
            );
        }
        else if (currentState == *(int*)((char*)this + 0x120)) { // m_stateConstant5
            result = processStateActionEffect(
                currentState,
                *(int*)((char*)this + 0xf4),  // m_stateActionParamA5
                *(int*)((char*)this + 0xb0)   // m_stateActionParamB5
            );
        }
        else if (currentState == *(int*)((char*)this + 0x124)) { // m_stateConstant6
            // Multiple actions for this state
            processStateActionEffect(
                currentState,
                *(int*)((char*)this + 0xf8),  // m_stateActionParamA6
                *(int*)((char*)this + 0xb4)   // m_stateActionParamB6
            );
            processStateActionEffect(
                *(int*)((char*)this + 0x14), // currentState again
                *(int*)((char*)this + 0xfc), // m_stateActionParamC6
                *(int*)((char*)this + 0xb8)  // m_stateActionParamD6
            );
            processStateActionEffect(
                *(int*)((char*)this + 0x14),
                *(int*)((char*)this + 0x100), // m_stateActionParamE6
                *(int*)((char*)this + 0xbc)   // m_stateActionParamF6
            );
            processStateActionEffect(
                *(int*)((char*)this + 0x14),
                *(int*)((char*)this + 0x110), // m_stateActionParamG6
                *(int*)((char*)this + 0xa8)   // m_stateActionParamH6
            );
            result = finalizeStateActions(
                *(int*)((char*)this + 0x14),
                *(int*)((char*)this + 0x104), // m_stateActionParamI6
                (int*)((char*)this + 0xd0)    // m_stateActionResultBuffer6
            ); // FUN_0060add0
            return result;
        }
        else if (currentState == *(int*)((char*)this + 300)) { // m_stateConstant7 (0x12c)
            result = processStateActionEffect(
                currentState,
                *(int*)((char*)this + 0x10c), // m_stateActionParamA7
                *(int*)((char*)this + 0xc0)   // m_stateActionParamB7
            );
        }
    }
    return result;
}
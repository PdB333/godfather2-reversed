// FUNC_NAME: StateMachineDispatcher::updateState

// Global state variables for the state machine
extern int g_previousStateIndex;                    // DAT_01130548 - previous state index
extern int g_stateFlagsBitfield;                    // DAT_01130590 - bitfield controlling state machine behavior
extern int g_nextStateIndex;                        // DAT_00e5672c - next state index to transition to

// Array of state data structures (12 bytes per entry, first byte = active flag)
extern uint8_t g_stateDataArray[];                  // UNK_00d89450 - offset 0: active flag (bit 0)

// Array of state handler entries (12 bytes per entry, first 4 bytes = function pointer)
extern uint8_t g_stateHandlerEntries[];             // UNK_00d8944c - offset 0: void (__fastcall *handler)(void* param_1, int oldStateIndex)

// External helper: sets/clears a state active flag based on the given value
void __fastcall setStateActiveFlag(uint32_t flag);  // FUN_0068c590 - sets flag if flag != 0

void __fastcall StateMachineDispatcher::updateState(void* callerThis)
{
    int oldStateIndex;
    int handlerOffset;

    oldStateIndex = g_previousStateIndex;

    // Check if state transitions are allowed (bit 4 of the flags field)
    if ((g_stateFlagsBitfield >> 4 & 1) == 0) {
        // Compute offset into state arrays (12-byte stride per state)
        handlerOffset = g_nextStateIndex * 12;

        // Update the previous state index to the new one
        g_previousStateIndex = g_nextStateIndex;

        // Invert the active flag for the new state (bit 0 of state data)
        setStateActiveFlag(~(g_stateDataArray[g_nextStateIndex * 12]) & 1);

        // Call the handler for the new state, passing the old state index as second argument
        (*(void (__fastcall**)(void*, int))(&g_stateHandlerEntries + handlerOffset))(callerThis, oldStateIndex);
    }
}
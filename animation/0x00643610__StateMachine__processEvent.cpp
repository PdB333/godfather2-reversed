// FUNC_NAME: StateMachine::processEvent
// Function at 0x00643610: Handles state machine events with dispatch based on event type.
// this (param_1) is likely the state machine instance; event type passed in EAX (in_EAX).
// unaff_EDI appears to be a separate context object (e.g., owner or parent) with offset 0x0c and 0x10 for state timers/flags.
// Offsets on this: +0x18 maybe "previousState", +0x1c "currentState"; copied to update state.
void __fastcall StateMachine::processEvent(int this, int eventType) // Note: actual calling convention may be __thiscall with this in ECX, eventType in EAX.
{
    // eventType is in EAX via __fastcall or custom register passing
    if (eventType == 5) {
        // Event 5: likely a specific transition (e.g., kEventEnterCover)
        FUN_00642ec0(); // side effect, possibly global or belongs to this
        return;
    }
    if (eventType == 0xc) {
        // Event 12: (e.g., kEventExitCover)
        FUN_00643310(); // perform transition logic
        *(int*)(this + 0x1c) = *(int*)(this + 0x18); // copy previous state to current state
        FUN_00642880(this); // update state machine internals
        *(int*)(unaff_EDI + 0x0c) = -1; // reset timer or flag in owner context
        return;
    }
    if (eventType == 0xd) {
        // Event 13: (e.g., kEventTakeDamage)
        FUN_006433b0(); // perform transition logic
        *(int*)(this + 0x1c) = *(int*)(this + 0x18); // copy previous state to current state
        FUN_00642880(this); // update state machine internals
        *(int*)(unaff_EDI + 0x10) = -1; // reset another timer or flag in owner context
        return;
    }
    // Default: unrecognized event
    FUN_00642fc0();
    return;
}
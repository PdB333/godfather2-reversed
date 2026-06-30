// FUNC_NAME: StateMachine::onStateTimerExpired
// Address: 0x00709440
// Called when a state timer expires to handle state transition.
// Checks if the current state is a specific type (hash 0x383225a1) and the new state is the embedded subobject at offset 0x48,
// then performs cleanup, calls callback, copies state references, and resets the timer.

void __fastcall StateMachine::onStateTimerExpired(
    StateMachine* this,
    int newStatePtr,        // +0x748 on stack - pointer to new state (or 0)
    int flagA,              // +0x24A4 on stack - triggers FUN_00705760 cleanup
    int flagB               // +0x24B0 on stack - triggers FUN_004daf90 release
)
{
    // Fields at known offsets
    uint32_t flags         = *(uint32_t*)((uintptr_t)this + 0x1D0);
    float timer            = *(float*)   ((uintptr_t)this + 0x2A8);
    int currentStatePtr    = *(int*)     ((uintptr_t)this + 0x214);

    // Check conditions: bit 3 set, timer expired, current state valid and not special state 0x48
    if ( ((flags >> 3) & 1) == 0 ) return;
    if ( timer > 0.0f ) return;
    if ( currentStatePtr == 0 || currentStatePtr == 0x48 ) return;

    // Get base of current state object (assumes embedded at offset -0x48 from state pointer)
    int* baseState = (currentStatePtr == 0) ? 0 : (int*)(currentStatePtr - 0x48);
    // Virtual call at vtable+0x10: likely isA(uint32_t hash) check
    char isTargetState = (*(char(__thiscall**)(int, uint32_t))(*(uintptr_t*)baseState + 0x10))(currentStatePtr, 0x383225a1);
    if ( !isTargetState ) return;

    // Compute base of new state from stack parameter
    int newStateBase = (newStatePtr == 0) ? 0 : newStatePtr - 0x48;
    if ( newStateBase != (int)this ) return;  // new state must be the embedded subobject inside this

    // --- Transition logic ---
    if ( flagA != 0 )
    {
        stateCleanup(this);               // FUN_00705760 - possibly destroy current state
    }

    // Call global function pointer at address 0x258
    ((void (*)(int))0x258)(0);

    if ( flagB != 0 )
    {
        // FUN_004daf90 - likely a release on the object pointed to by flagB parameter
        releaseObject((void*)flagB);
    }

    // Copy state references (e.g., previous = current)
    copyStateRefs(this + 0x258, this + 0x268);  // FUN_00708f80

    // Reset state timer at offset 0x3C
    resetTimer(this + 0x3C);                    // FUN_004088c0
}
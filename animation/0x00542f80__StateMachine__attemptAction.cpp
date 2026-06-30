// FUNC_NAME: StateMachine::attemptAction
uint __thiscall StateMachine::attemptAction(void *this, uint actionId) {
    // Virtual function at vtable offset 0x1DC (index 119) - returns bool
    bool cond1 = (**(bool (__thiscall**)(void*))((uint*)this + 119))(); // vtable+0x1DC
    if (cond1) {
        // Virtual function at vtable offset 0x1E0 (index 120) - returns bool
        bool cond2 = (**(bool (__thiscall**)(void*))((uint*)this + 120))(); // vtable+0x1E0
        if (cond2) {
            // Local output parameter
            uint result;
            // Virtual function at vtable offset 0x1EC (index 123) - takes actionId and &result
            (**(void (__thiscall**)(void*, uint, uint*))((uint*)this + 123))(this, actionId, &result); // vtable+0x1EC
            // Virtual function at vtable offset 500 (0x1F4, index 125) - takes &result and returns int
            int status = (**(int (__thiscall**)(void*, uint*))((uint*)this + 125))(this, &result); // vtable+0x1F4
            return (uint)(status == 0);
        }
    }
    // Return the high byte of the condition (likely an error code)
    return (uint)(cond1 ? 0 : 0xFFFFFF00) & 0xFFFFFF00;
}
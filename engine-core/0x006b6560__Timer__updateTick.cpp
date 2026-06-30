// FUNC_NAME: Timer::updateTick
// Function address: 0x006b6560
// Reconstructed member function for a timer/countdown component.
// Fields:
//   +0x74: uint32 tickCount (incremented each call)
//   +0x80: float remainingTime (?) 
//   +0x34: uint32 flags (bit 29 = active flag? cleared if not paused)
// Global _DAT_00d577a0: some time threshold (likely 0.0f or minimum time)

void __thiscall Timer::updateTick(int this, undefined4 param_2) {
    // Call helper function with the passed parameter (likely a context or owner pointer)
    FUN_006b5c50(param_2);

    // Increment tick counter
    *(int*)(this + 0x74) = *(int*)(this + 0x74) + 1;

    // Check if remaining time has elapsed and timer is not flagged as inactive
    if ((*(float*)(this + 0x80) <= *(float*)0x00d577a0) &&
        (*(uint*)(this + 0x34) >> 0x1d & 1) == 0) {  // bit 29 clear = active
        // Timer expired – trigger timeout action
        FUN_006b59f0();
        return;
    }

    // Timer still running – call regular update
    FUN_006b2f70();
}
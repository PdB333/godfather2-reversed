// FUNC_NAME: XInputController::SetRumble
// Address: 0x008e0350
// Role: Applies rumble (vibration) to the controller, with optional immediate stop and flag-based scaling.
// Offsets: +0x22c flags, +0x230 rumble input value, +0x234 previous rumble time/strength, +0x48 lock/refcount, +0x58 vtable ptr, +0x250/0x258 alternate state

void __thiscall XInputController::SetRumble(void* this, undefined4 rumbleValue, char bStopImmediately) {
    float randomFloat;
    undefined** local_18;
    int lockPtr; // points to this+0x48 (scope guard)
    undefined4 local_c;
    undefined4 local_10;
    undefined*** local_8;
    undefined1 local_4;

    // Store rumble input value at offset +0x230
    *(undefined4*)((int)this + 0x230) = rumbleValue;

    // Get a random float (likely for subtle rumble variation)
    randomFloat = (float)FUN_008dab60(); // GetRandomFloat? maybe time-based

    // Apply rumble: left motor = constant (duration?) - previousRumble, right motor = -randomFloat
    // DAT_00e44564 is likely a time constant (e.g., 1.0f) or max rumble magnitude
    FUN_008de620(DAT_00e44564 - *(float*)((int)this + 0x234), (float)-randomFloat); // SetRumble?

    if (bStopImmediately != '\0') {
        // Stop rumble immediately via vtable call at index 0x28 (10th function)
        // 0x80 likely a flag/parameter for stopping
        (**(code**)(*(int*)((int)this + 0x58) + 0x28))(0x80);
        FUN_008dfd20(); // Possibly flush or finalize
        return;
    }

    // Compute flags: if rumbleValue != 0, flags = 2, else flags = 0
    *(uint*)((int)this + 0x22c) = -(uint)(*(int*)((int)this + 0x230) != 0) & 2;

    FUN_008de4d0(1); // Some initialization/state change

    // Scoped guard / smart pointer manipulation starting at this+0x48
    lockPtr = (int)this + 0x48;
    local_18 = &PTR_FUN_00e31e2c; // global vtable or function pointer
    local_10 = 0;
    if (lockPtr != 0) {
        local_10 = *(undefined4*)((int)this + 0x4c);
        *(int**)((int)this + 0x4c) = &lockPtr; // swap pointers (ownership transfer)
    }
    local_8 = &local_18;
    local_4 = 0;

    // Select state source based on flags
    if (*(int*)((int)this + 0x22c) == 0) {
        local_c = *(undefined4*)((int)this + 0x250); // alternate state 1
    } else {
        local_c = *(undefined4*)((int)this + 600); // offset 0x258 alternate state 2
    }

    FUN_00408a00(&local_c, 0); // Likely copies/processes the state

    if (lockPtr != 0) {
        FUN_004daf90(&lockPtr); // Release guard / unlock
    }

    FUN_008dfd20(); // Finalize / flush
    return;
}
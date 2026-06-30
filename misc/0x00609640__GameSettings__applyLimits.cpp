// FUNC_NAME: GameSettings::applyLimits
void __thiscall GameSettings::applyLimits(int arg1, int arg2, int arg3, int extraEAX) {
    // This appears to be a settings application method, likely called after loading or changing
    // configuration values. It clamps two global variables to a minimum/maximum of 0xae (174)
    // and sets a global flag to 1. It also calls a virtual function at offset 300 in the vtable,
    // passing a pointer to an array where arg1 is stored.
    int local_sum; // sum of arg1 and arg2 -> local_8
    int local_other_sum; // sum of extraEAX and arg3 -> local_4 (unused later)
    int local_array[2]; // passed to virtual call

    local_sum = arg1 + arg2;
    local_other_sum = extraEAX + arg3;
    local_array[0] = arg1;
    // Note: local_array[1] is uninitialized; possible the virtual function only reads the first element,
    // or the decompilation missed an initialization.

    // Call virtual function at vtable offset 300 (presumably an event handler like OnApplyLimits)
    (**(code **)(*(int *)this + 300))(this, local_array);

    // Enforce minimum limit on global variable DAT_012058d4 (likely a max value for something)
    if (g_maxSomething < 0xae) {
        g_maxSomething = 0xae;
    }

    // Cap global variable DAT_00f1598c at 0xae (if it exceeds 174)
    if (g_capValue > 0xae) {
        g_capValue = 0xae;
    }

    // Set global flag to indicate limits have been applied
    g_limitsApplied = 1;

    // Return void
}
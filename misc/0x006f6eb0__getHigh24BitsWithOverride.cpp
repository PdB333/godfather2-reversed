// FUNC_NAME: getHigh24BitsWithOverride
// Function address: 0x006f6eb0
// Returns (in_EAX & 0xFFFFFF00) unless a global flag is set, in which case calls an override function.
// The value in in_EAX is an implicit register parameter (set by caller in EAX).
uint getHigh24BitsWithOverride(uint overrideArg) {
    uint result;
    // in_EAX is the value of EAX at function entry (injected by Ghidra)
    result = in_EAX & 0xFFFFFF00; // Extract high 24 bits (e.g., base pointer or ID)
    if (g_overrideFlag != 0) { // Global debug/override flag at 0x0112aa10
        result = computeOverrideValue(overrideArg); // Call to FUN_006f66f0
    }
    return result;
}
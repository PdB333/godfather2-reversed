// FUNC_NAME: ValidationUtil::isWithinRange
// Address: 0x005dcb60
// Role: Validates whether two float values (this and a computed value) are within acceptable bounds.
// The function checks if a computed value (via FUN_005dd8a0) is between 0.0 and a global maximum (0x00e2b1a4),
// AND that *this (the object's stored float) is non-negative. Returns 1 if all conditions hold, else 0.

bool __thiscall ValidationUtil::isWithinRange(float *this, int param2, int param3, int in_EAX) {
    int result;
    float computedValue; // value written by FUN_005dd8a0

    // FUN_005dc670 likely performs an initialization or state check using in_EAX (e.g., a handle or session ID)
    result = FUN_005dc670(in_EAX);
    if (result != 0) {
        // FUN_005dd8a0 computes a value into computedValue based on param_3 (e.g., an index or timer)
        FUN_005dd8a0(param3, &computedValue);
        // Check: *unaff_ESI (computedValue) must be in [0.0, MAX_ACCEPTABLE_VALUE]
        // and *this (the member float) must also be non-negative.
        if ((computedValue >= 0.0f) && (computedValue <= *(float*)0x00e2b1a4) && (*this >= 0.0f)) {
            return true;
        }
    }
    return false;
}
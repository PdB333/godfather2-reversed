// FUNC_NAME: SomeClass::isValueInBounds
// Address: 0x005ddaf0
// Role: Checks if a float value (pointed by pValue) is within a valid range [0, MAX_VALUE] and that an internal state is initialized.

// This function likely belongs to a class that manages a bounded float attribute (e.g., health, reputation, charge).
// The constant DAT_00e2b1a4 is a global maximum value used in various checks.

bool __thiscall SomeClass::isValueInBounds(float *pValue, uint32_t someParam) {
    // in_EAX is a decompiler artifact; likely the this pointer was moved to ESI.
    // The original assembly: ECX = this, then moved to ESI.
    // The call to FUN_005dc670 uses a hidden parameter (in_EAX) that is not fully understood.
    // For reconstruction, we treat it as a call to an initialization check.
    bool isInitialized = (FUN_005dc670(someEaxParam) != 0);

    if (isInitialized) {
        // FUN_005dd8a0 presumably sets up or validates something with someParam.
        FUN_005dd8a0(someParam, this);

        // Check that this->someInternalValue is >= 0 and <= MAX_VALUE,
        // and that the input *pValue is >= 0.
        if ((this->internalValue >= 0.0f) && 
            (this->internalValue <= MAX_VALUE) && 
            (*pValue >= 0.0f)) {
            return true;
        }
    }
    return false;
}
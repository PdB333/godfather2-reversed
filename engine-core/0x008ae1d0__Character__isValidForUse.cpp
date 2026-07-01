// FUNC_NAME: Character::isValidForUse
// Address: 0x008ae1d0
// Role: Determines if a character is in a usable state (no ragdoll/vehicle, proper component state, and correct main state)
// Details: Checks for null ragdoll (+0xf0) and vehicle (+0xe4) pointers, verifies a referenced object's state (+0x24) is 3,
//          then checks a flag bit (bit6 of +0x7c) and a state variable (+0xd8) that must be 1 or (2 with additional function check)

bool __fastcall Character::isValidForUse(int thisPtr)
{
    char tempBool;
    int componentPtr;

    // Check that both ragdoll and vehicle pointers are null
    if (*(int *)(thisPtr + 0xf0) == 0 && *(int *)(thisPtr + 0xe4) == 0) {
        // If a component pointer is non-null, validate it
        if (*(int *)(thisPtr + 0x148) != 0) {
            componentPtr = getComponentObject(*(int *)(thisPtr + 0x148));
            if (componentPtr == 0) {
                return false;
            }
            // Required component state must be 3 (e.g., active/engaged)
            if (*(int *)(componentPtr + 0x24) != 3) {
                return false;
            }
        }
        // Check a flag (bit 6 of flags at +0x7c) – possibly "isAlive" or "isActive"
        if ((*(unsigned int *)(thisPtr + 0x7c) >> 6 & 1) != 0) {
            // Main state at +0xd8: allowed values are 1 or 2
            if (*(int *)(thisPtr + 0xd8) != 1) {
                // For state 2, an additional condition must be satisfied
                tempBool = checkState2Condition();
                if (tempBool == '\0') {
                    return false;
                }
                if (*(int *)(thisPtr + 0xd8) != 2) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}
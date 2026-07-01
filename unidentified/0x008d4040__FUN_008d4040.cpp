// FUNC_NAME: UnknownClass::clearActiveFlag
// Function address: 0x008d4040
// Role: Checks a flag at offset 0x81 and if set, calls a function with a global pointer, then clears the flag.

void UnknownClass::clearActiveFlag()
{
    // Check if the active flag at +0x81 is set (non-zero)
    if (this->activeFlag != 0) { // +0x81 byte flag
        // Call external function with a global data pointer (e.g., release lock or stop timer)
        someGlobalFunction(&g_someGlobalData); // 0x004086d0, DAT_0112f9dc
        // Clear the active flag
        this->activeFlag = 0; // +0x81
    }
}
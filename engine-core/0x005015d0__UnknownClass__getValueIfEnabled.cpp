// FUNC_NAME: UnknownClass::getValueIfEnabled
int UnknownClass::getValueIfEnabled(int thisPtr, int isEnabled)
{
    if (isEnabled != 0) {
        // If the flag is set, call the internal getter function and return its result.
        int result = FUN_005010d0(thisPtr); // +0x00 (possibly offset)
        return result;
    }
    // If not enabled, return 0 (null or false).
    return 0;
}
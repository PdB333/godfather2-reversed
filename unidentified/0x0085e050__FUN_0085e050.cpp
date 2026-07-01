// FUNC_NAME: SomeClass::checkAndReturnValue
uint __fastcall SomeClass::checkAndReturnValue(int thisPtr)
{
    uint result;
    int field8 = *(int *)(thisPtr + 8); // +0x8: state/type field

    if (field8 != 0 && field8 != 0x48) {
        // If field is non-zero and not 0x48, call helper function
        result = FUN_0079e920();
        return result;
    }
    // Otherwise, return the high 24 bits of the input EAX (masked)
    return in_EAX & 0xffffff00;
}
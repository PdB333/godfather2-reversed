// FUNC_NAME: UnknownClass::checkStateAndCleanup
void __thiscall UnknownClass::checkStateAndCleanup(int *this)
{
    // +0x00: type/state identifier (int)
    // +0x08: flag byte (bool)
    // Check if the object type is non-zero and not a specific invalid type (0x48)
    if ((*this != 0) && (*this != 0x48)) {
        // Call cleanup or reset routine
        FUN_007376a0();
    }
    // If a boolean flag at offset 8 is set, log a debug message
    if ((char)this[2] != '\0') {
        // Temporary structure for debug logging
        int prefix = DAT_0112aa84;
        int param2 = 0;
        char suffix = 0;
        FUN_00408a00(&prefix, 0);
    }
}
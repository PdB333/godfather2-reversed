//FUNC_NAME: UnknownClass::callIfEnabled
// Function address: 0x00589070
// Role: Checks a boolean flag at offset 0x70 and calls another function if set.

void __thiscall UnknownClass::callIfEnabled(void)
{
    // Check if the flag at this+0x70 is non-zero
    if (*(char *)(this + 0x70) == '\0') {
        return;
    }
    // Call the internal function (likely an update or processing routine)
    FUN_00b99fcb(); // TODO: identify this function
}
// FUNC_NAME: SomeClass::convertValueConditional
void __thiscall SomeClass::convertValueConditional(byte *flags, undefined4 inputValue)
{
    // FUN_00595490 likely converts a value to float (possibly from double or int)
    double result = FUN_00595490(inputValue); // initial conversion

    // Check bit 0 of the flags byte
    if (*flags & 1)
    {
        // If flag is set, convert the float back and forth (possible precision adjustment)
        result = FUN_00595490((float)result); // convert to float then through function
        FUN_00595490((float)result); // second call without storing (side effect?)
    }
    // Otherwise nothing
}
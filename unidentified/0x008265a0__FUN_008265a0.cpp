// FUNC_NAME: SomeClass::someMethod
void SomeClass::someMethod(void)
{
    // Stack variables for a 3-component value (likely a vector or color)
    undefined4 value1; // +0x00
    undefined4 value2; // +0x04
    undefined1 value3; // +0x08

    value1 = DAT_0112db7c; // Load a global constant (likely a static initializer)
    value2 = 0;
    value3 = 0;
    FUN_00408a00(&value1, 0); // Call function with pointer to the initialized data and a zero flag
    return;
}
// FUNC_NAME: SomeClass::setValue
void __thiscall SomeClass::setValue(int this, int value)
{
    // Store the value at offset +0x14 (likely a member variable)
    *(int *)(this + 0x14) = value;

    // If the global debug/initialization flag is set, call the debug update function
    if (DAT_01129c4c != 0) {
        FUN_0093b0e0(); // Likely debugPrint or updateDebug
    }
}
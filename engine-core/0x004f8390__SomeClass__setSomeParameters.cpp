// FUNC_NAME: SomeClass::setSomeParameters
void SomeClass::setSomeParameters(int param1, int param2)
{
    // Local array of 3 values: 0x20, 0x30, 0x40 (likely some configuration constants)
    int localValues[3];
    localValues[0] = 0x20; // +0x00: first value
    localValues[1] = 0x30; // +0x04: second value
    localValues[2] = 0x40; // +0x08: third value

    // Call to internal function with the parameters and the array
    FUN_004eba90(param1, param2, localValues, 3);
}
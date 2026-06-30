//FUNC_NAME: SomeClass::processBlendData
void SomeClass::processBlendData(float inputValue)
{
    // unaff_EDI is likely the 'this' pointer (stored in EDI register)
    // Check flag at offset +4 (bit 0) – possibly indicates a special blend mode
    if ((*(byte *)(this + 4) & 1) != 0) {
        // If flag set, apply square root (or similar) twice
        float temp = FUN_00595490(inputValue);  // likely sqrt or fabs
        temp = FUN_00595490(temp);              // second application
        FUN_00595490(temp);                     // result discarded? Possibly side effect
    }
    // Initialize a local object of size 28 bytes (e.g., a temporary blend state)
    SomeBlendState localState;  // local_20, 28 bytes
    FUN_0059bb50(&localState); // constructor or reset
    // Call virtual function at vtable offset 0x14 (e.g., applyBlend)
    (*(void (**)(SomeBlendState *))(*(int *)this + 0x14))(&localState);
}
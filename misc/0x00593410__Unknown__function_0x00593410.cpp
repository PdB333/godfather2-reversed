// FUNC_NAME: Unknown::function_0x00593410
// Address: 0x00593410
// This function appears to take a pointer (param_1) and a value (param_2).
// It initializes a local 32-byte structure with zeros and a global constant,
// then calls a setup function (FUN_00593210) passing the local structure and
// the value that was in EAX at entry (likely a second or third parameter).
// Then it reads a data pointer from offset +0x04 of param_1, checks a state
// byte (offset +0x04 of the data structure) and selects a value from either
// offset +0x0C or +0x20. Finally, it calls another function with param_2 and
// the selected value.

void __thiscall FUN_00593410(void* thisPtr, uint32_t param2)
{
    // 32-byte local buffer, possibly a transform or matrix
    struct LocalBuffer {
        uint32_t data[8];
    } buffer;

    buffer.data[0] = 0;
    buffer.data[1] = 0;
    buffer.data[2] = 0;
    buffer.data[3] = DAT_00E2B1A4; // Global constant
    buffer.data[4] = 0;
    buffer.data[5] = 0;
    buffer.data[6] = 0;
    buffer.data[7] = DAT_00E2B1A4; // Global constant

    // The decompiler shows that the second argument to the following call
    // is the value that was in EAX at function entry. This might indicate
    // that the function actually receives a third parameter via register.
    // We'll assume it's the same as `param2` or perhaps the `this` pointer.
    // For reconstruction, we pass `param2` as a guess.
    FUN_00593210(&buffer, param2);

    // Retrieve a pointer from this+0x04
    void* someData = *(void**)((uint8_t*)thisPtr + 0x04);

    uint32_t selectedValue;
    // Check byte at someData+0x04 (low byte of a uint)
    if ((*((uint8_t*)someData + 0x04) & 0xFF) < 10) {
        selectedValue = *(uint32_t*)((uint8_t*)someData + 0x0C);
    } else {
        selectedValue = *(uint32_t*)((uint8_t*)someData + 0x20);
    }

    // Call final function with param2 and the selected value
    FUN_00586DF0(param2, selectedValue);
}
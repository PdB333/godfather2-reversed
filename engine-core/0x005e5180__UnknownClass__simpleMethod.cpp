// FUNC_NAME: UnknownClass::simpleMethod
// Function address: 0x005e5180
// Calls FUN_005f0560 with input and two local buffers.
void __fastcall UnknownClass::simpleMethod(void* this, uint input)
{
    uint8 byteVal;          // 1-byte output
    uint8 fourByteBuf[4];   // 4-byte output buffer

    // Call internal utility function
    FUN_005f0560(input, &byteVal, fourByteBuf);
    // No usage of locals – likely a side-effect call or debug remnant
    return;
}
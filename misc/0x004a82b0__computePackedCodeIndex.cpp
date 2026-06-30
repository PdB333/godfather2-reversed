// FUNC_NAME: computePackedCodeIndex
void __fastcall computePackedCodeIndex(uint32_t* codeFields) // codeFields[4] (0x00, 0x04, 0x08, 0x0C)
{
    uint32_t digit0 = codeFields[0]; // +0x00
    uint32_t digit1 = codeFields[1]; // +0x04
    uint32_t digit2 = codeFields[2]; // +0x08
    uint32_t digit3 = codeFields[3]; // +0x0C

    // Compute base-33 packed value: digit0*33^3 + digit1*33^2 + digit2*33 + digit3
    uint64_t intermediate = (uint64_t)digit0 * 33 + digit1;
    intermediate = intermediate * 33 + digit2;
    uint64_t result64 = intermediate * 33 + digit3;
    uint32_t index = (uint32_t)result64; // low 32 bits used as index

    // Dispatch the computed index with a flag of 0
    FUN_004a8180(index, 0);
}
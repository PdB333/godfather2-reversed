// FUNC_NAME: MathUtils::alignedNegate
void __cdecl MathUtils::alignedNegate(uint32_t* inEAX)
{
    // Compute: ((*inEAX >> 1) + 1) * 2 as 64-bit to detect overflow
    uint64_t temp = ((uint64_t)(*inEAX >> 1) + 1) * 2;

    // If the 64-bit result exceeds 32 bits, saturate to 0xFFFFFFFF; otherwise take low 32 bits
    uint32_t satVal;
    if ((temp >> 32) != 0) {
        satVal = 0xFFFFFFFF;
    } else {
        satVal = (uint32_t)temp;
    }

    // Apply two's complement negation and pass to the callee (likely a memory or math utility)
    sub_009c8e50(0 - satVal);
}
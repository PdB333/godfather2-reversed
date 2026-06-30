// FUN_00429190: EARSMathHelper::forwardProcessInput16Byte
// Wrapper function that copies two 16‑byte input structures from param_2 and param_3
// into local stack copies and forwards them to the core internal function FUN_00428870.
// param_1 is unused (likely a discarded this/handle due to compiler optimization).
void EARSMathHelper::forwardProcessInput16Byte(uint32_t unusedThis, Float4* inputA, Float4* inputB)
{
    // Copy 16 bytes from inputA into local stack (two 8-byte halves)
    Float4 localA;
    localA.qwords[0] = inputA->qwords[0];
    localA.qwords[1] = inputA->qwords[1];

    // Copy 16 bytes from inputB into local stack
    Float4 localB;
    localB.qwords[0] = inputB->qwords[0];
    localB.qwords[1] = inputB->qwords[1];

    // Delegate to the actual processing routine with the copied data
    FUN_00428870(&localA, &localB);
}
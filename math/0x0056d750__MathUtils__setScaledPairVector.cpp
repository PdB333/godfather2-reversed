// FUNC_NAME: MathUtils::setScaledPairVector
// Address: 0x0056d750
// Role: Sets a 4-float output array with two zero entries and two equal scaled values.
// The input float is scaled by global factor DAT_00e2cd54 (likely a conversion constant e.g. degrees to radians).
// Two internal engine functions (FUN_00b99fcb and FUN_00b99e20) are called, possibly for FPU state management.
// Output array: [input*factor, 0.0, 0.0, input*factor]

void setScaledPairVector(float input, float* outArray4)
{
    // Zero out elements 2 and 1 (second and third slots)
    outArray4[2] = 0.0f;
    outArray4[1] = 0.0f;

    // Scale input by global constant (e.g., DEG_TO_RAD or other factor)
    float scaled = input * DAT_00e2cd54;

    // Engine FPU state save/init (context push)
    FUN_00b99fcb();

    // Set first element to scaled value
    outArray4[0] = scaled;

    // Engine FPU state restore/finalize (context pop)
    FUN_00b99e20();

    // Same scaled value placed into last element
    outArray4[3] = scaled;
}
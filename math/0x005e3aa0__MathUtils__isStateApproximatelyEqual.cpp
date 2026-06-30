// FUNC_NAME: MathUtils::isStateApproximatelyEqual
bool __fastcall isStateApproximatelyEqual(int* stateA, int* stateB)
{
    // State struct: first int is an exact match ID, next 4 floats (position/quaternion)
    // Constants from game globals: mask = 0x7FFFFFFF, epsilon < 0.0001f (approx)
    constexpr uint32_t ABS_MASK = 0x7FFFFFFF;   // DAT_00e44680
    constexpr float EPSILON = 0.0001f;          // DAT_00e44598

    // Exact integer comparison for first field (e.g., type/ID)
    if (stateA[0] != stateB[0])
        return false;

    // Compare 4 float fields with absolute difference tolerance
    for (int i = 1; i <= 4; i++)
    {
        float diff = (float)stateA[i] - (float)stateB[i];
        uint32_t absDiffBits = reinterpret_cast<uint32_t&>(diff) & ABS_MASK;
        float absDiff = reinterpret_cast<float&>(absDiffBits);
        if (absDiff >= EPSILON)
            return false;
    }
    return true;
}
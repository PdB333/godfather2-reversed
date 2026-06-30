// FUNC_NAME: compareObjectPosition
// Function at 0x005e3aa0 - Compares two objects' position data (ID + 4 floats) within epsilon
// Returns 0 if positions match (ID equal and all float differences < threshold), else 1
// Uses __fastcall: first arg in ECX (param_1), second arg in EDX (in_EAX)
bool __fastcall compareObjectPosition(const int* pObjectA, const int* pObjectB)
{
    // Constants: assume DAT_00e44680 = 0x7FFFFFFF (abs mask for IEEE 754 float bits)
    //            DAT_00e44598 = small float threshold (e.g., 0.001f)
    static const unsigned int ABS_MASK = 0x7FFFFFFF;
    static const float EPSILON = *(const float*)&DAT_00e44598; // treat as float

    // First field: object ID (int)
    if (pObjectA[0] != pObjectB[0])
        return true;   // IDs differ

    // Next four fields: position components (x,y,z,w) as floats stored as int
    for (int i = 1; i <= 4; ++i)
    {
        float diff = (float)pObjectA[i] - (float)pObjectB[i];
        unsigned int absDiffBits = (*(unsigned int*)&diff) & ABS_MASK;
        float absDiff = *(float*)&absDiffBits;
        if (absDiff >= EPSILON)
            return true;   // component out of range
    }

    return false; // all components within epsilon, IDs match -> equal
}
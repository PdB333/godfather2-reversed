// FUNC_NAME: PriorityCompare
// Address: 0x00590d40
// Role: Compares two objects/values and returns a priority/score. Uses float reinterpreted as pointer for object A.
// Callees: 0x00591c00 (resetObject), 0x00591160 (getScore)

float PriorityCompare(int unused, float rawValue, int contextPtr)
{
    int objectPtr = (int)rawValue;                     // rawValue is actually a pointer stored as float
    float localScore = 0.0f;                           // in_XMM0_Da

    // Check if context struct's size at +4 is <= size of object's sub-struct at +4 -> +0xC
    if (*(uint *)(contextPtr + 4) <= *(uint *)(*(int *)(objectPtr + 4) + 0xC)) {
        localScore = 0.0f;
        rawValue = 0.0f;                               // reset the pointer to null
        FUN_00591c00(&rawValue);                       // possibly initialize or clear
    }

    // If a version/state byte at offset +1 is below 2, return default constant
    if (*(char *)(objectPtr + 1) < 2) {
        return (float)DAT_00e2b1a4;                    // global constant (0x00e2b1a4)
    }

    FUN_00591160();                                    // first score computation (side effects)
    rawValue = localScore;                             // update rawValue with localScore
    FUN_00591160();                                    // second score computation

    if (localScore < rawValue) {
        localScore = rawValue;                         // take max
    }
    return localScore;
}
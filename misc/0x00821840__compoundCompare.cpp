// FUNC_NAME: compoundCompare
// Address: 0x00821840
// Role: Three-value comparison helper. Determines ordering/containment based on two auxiliary comparison functions.
// Calls FUN_00835a00 (likely "isGreater" or "contains") and FUN_00835ae0 (likely "isLess" or "hasFlag").
// Returns 1 if (result1 != 0 && result2 != 0) || result3 != 0, except if result1==0 && result2==0 returns 0 immediately.
int __cdecl compoundCompare(int value1, int value2, int value3)
{
    char result1; // FUN_00835a00(value3, value2) - e.g., isGreater(value3, value2)
    char result2; // FUN_00835ae0(value1, value2) - e.g., isLess(value1, value2)
    char result3; // FUN_00835a00(value1, value3)

    result1 = FUN_00835a00(value3, value2);
    result2 = FUN_00835ae0(value1, value2);
    result3 = FUN_00835a00(value1, value3);

    // If both false, return 0 early.
    if (result1 == '\0') {
        if (result2 == '\0') {
            return 0;
        }
    }
    else if (result2 != '\0') {
        return 1; // both true
    }

    // Fallback: return result3
    if (result3 != '\0') {
        return 1;
    }
    return 0;
}
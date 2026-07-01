// FUNC_NAME: UnknownClass::hasMultipleMaxValues
bool __fastcall UnknownClass::hasMultipleMaxValues(void* thisPtr) {
    int firstValue = getValueByIndex(0); // FUN_008b4e20
    uint count = *(uint*)((int)thisPtr + 0x1b0); // number of elements
    bool hasDuplicateMax = false;

    if (count > 1) {
        int currentMax = firstValue;
        for (uint i = 1; i < count; i++) {
            int currentValue = getValueByIndex(i);
            if (currentValue == currentMax) {
                hasDuplicateMax = true;
            } else if (currentValue > currentMax) {
                currentMax = currentValue;
                hasDuplicateMax = false;
            }
            // else: keep hasDuplicateMax unchanged
        }
    }
    return hasDuplicateMax;
}
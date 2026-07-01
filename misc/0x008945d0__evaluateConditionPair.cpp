// FUNC_NAME: evaluateConditionPair
void evaluateConditionPair(int conditionType, void* conditionData, void* targetData, bool useExtendedFlags)
{
    int* dataPtr = (int*)conditionData;
    int* targetPtr = (int*)targetData;
    uint extendedFlags = 0;
    float valueA;
    float valueB;

    if (useExtendedFlags) {
        extendedFlags = *(uint*)((int)conditionData + 0xc); // conditionData +0x0C: extra flags word
    }

    // First extraction: read value at conditionData+0x08
    valueA = 0.0f;
    char result1 = FUN_00893e70(&valueA, *(undefined4*)((int)conditionData + 8), targetData, 1, 1, 0);
    if (result1) {
        // Second extraction: read value at conditionData+0x04
        valueB = 0.0f;
        char result2 = FUN_00893e70(&valueB, *(undefined4*)((int)conditionData + 4), targetData, 1, 1, 0);
        if (result2) {
            // Compare the two extracted values based on conditionType
            bool conditionMet = false;
            if (conditionType == 0xd) {
                // valueA must be less than valueB? (original: if (valueA <= valueB) return; so conditionMet when valueA > valueB)
                conditionMet = (valueA > valueB);
            } else if (conditionType == 0xe) {
                // valueA must be greater than valueB? (original: if (valueB <= valueA) return; so conditionMet when valueB > valueA)
                conditionMet = (valueB > valueA);
            } else {
                return;
            }

            if (conditionMet) {
                uint flags = *(byte*)((int)conditionData + 3) & 3; // conditionData +0x03: low 2 bits
                if ((*(byte*)((int)targetData + 0x10) & 5) != 0) { // targetData +0x10: flags, bit0 and bit2
                    flags |= 0x80000000; // set high bit
                }
                // Perform final extraction with different parameters
                FUN_00893e70(&valueA, *(undefined4*)((int)conditionData + 4), targetData, 2, flags, extendedFlags);
            }
        }
    }
}
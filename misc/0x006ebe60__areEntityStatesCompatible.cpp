// FUNC_NAME: areEntityStatesCompatible
bool areEntityStatesCompatible(int *pObjectA, int *pObjectB) {
    bool result = false;

    // Check for null pointers and ensure the target object is valid
    if (pObjectA != nullptr && pObjectB != nullptr &&
        *pObjectB != 0 &&
        *pObjectB != 0x48 &&           // 0x48 may indicate invalid/removed state
        pObjectB[2] != 0 &&
        pObjectB[2] != 0x48) {          // Field at offset 8 also must not be 0 or 0x48

        int adjustedFieldB = pObjectB[2] - 0x48;   // Derived from third field of B
        int adjustedFieldA = *pObjectA - 0xc;      // Derived from first field of A

        // Call internal comparator returning 0 on equality
        char cmpResult = FUN_00898330(adjustedFieldB, adjustedFieldA);
        result = (cmpResult == '\0');
    }

    return result;
}
// FUNC_NAME: HashMapTable::lookupValue
int __thiscall HashMapTable::lookupValue(int this, int primaryHash, int* secondaryKey, int* outStruct)
{
    int matchedPrimary;
    uint rowIndex;
    uint colIndex;
    int* pairPtr;
    uint numPairs;

    // Determine initial column index based on whether outStruct was provided
    colIndex = (uint)(outStruct != nullptr);

    // If secondaryKey is provided, attempt to resolve it into an outStruct
    if (secondaryKey != nullptr) {
        FUN_006a7890(&outStruct, &secondaryKey);
        if (outStruct != nullptr) {
            colIndex = *(uint *)(outStruct + 4);
        }
    }

    // Check if hash table is active and column index is within bounds
    if (*(int *)(this + 0x434) != 0 && colIndex < *(uint *)(this + 0x2c)) {
        matchedPrimary = FUN_004dafd0(primaryHash);
        numPairs = *(uint *)(this + 0x28);
        if (numPairs != 0) {
            pairPtr = (int *)(this + 0x30);
            for (rowIndex = 0; rowIndex < numPairs; rowIndex++) {
                if (*pairPtr == matchedPrimary) {
                    // Return value from 2D table: each row has 8 entries (0x20 bytes)
                    return *(int *)(this + 0x34 + (colIndex + rowIndex * 8) * 4);
                }
                pairPtr += 8; // each pair entry is two ints (8 bytes)
            }
        }
    }
    return 0;
}
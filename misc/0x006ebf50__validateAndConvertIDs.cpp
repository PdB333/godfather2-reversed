// FUNC_NAME: validateAndConvertIDs
// Address: 0x006ebf50
// Validates two ID-like values and calls a processing function with converted indices.
// param_1 points to a struct containing a base ID at offset 0.
// param_2 points to an array/struct containing type flags at offset 0 and index/count at offset 8.
// Returns 0 always.

int __thiscall validateAndConvertIDs(int* thisStruct, int* stateInfo) {
    int convertedIndex;

    // Null checks and structural validation
    if (thisStruct == (int*)0x0 || stateInfo == (int*)0x0) {
        return 0;
    }
    if (*stateInfo == 0) {
        return 0;
    }
    // Check that *stateInfo is not 0x48 (invalid state?) and stateInfo[2] is not 0 or 0x48
    if (*stateInfo == 0x48 || stateInfo[2] == 0 || stateInfo[2] == 0x48) {
        return 0;
    }

    // Convert stateInfo[2] to an index: if zero -> 0, else subtract base 0x48
    if (stateInfo[2] == 0) {
        convertedIndex = 0;
    } else {
        convertedIndex = stateInfo[2] - 0x48; // subtract base offset 0x48
    }

    // Call processing function: pass converted index and (thisStruct[0] - 0x1a)
    FUN_008982e0(convertedIndex, *thisStruct - 0x1a);
    return 0;
}
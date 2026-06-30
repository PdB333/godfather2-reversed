// FUNC_NAME: FastMap::findOrInsertPair
int __thiscall FastMap::findOrInsertPair(int this) {
    int* pBegin = *(int**)(this + 8);   // +0x8: pointer to first element
    int* pEnd = *(int**)(this + 0xC);   // +0xC: pointer past last element
    int* pOriginalEnd;
    int compareResult;
    int* pCurrent;
    int* pShift;
    int newPair[2];
    int returnVal;

    // Validate that container is not empty and first key is valid
    if ((pBegin > pEnd) || (pEnd == nullptr) || (*pBegin == -1)) {
        // Assertion: "value expected", likely a failed precondition
        pBegin = (int*)FUN_00627a20(this, 1, "value expected");
        pEnd = (int*)extraout_ECX;   // restored from saved register (unusual)
    }

    // Compute pointer to the element that should contain the key based on alignment
    // This arithmetic shifts pBegin backwards by 2 * number of elements (in bytes)
    pBegin = (int*)((int)pBegin - 2 * (((int)pBegin - (int)pEnd) >> 3));

    newPair[1] = -1;   // placeholder value, maybe unused

    // Compare the key at pBegin with something based on offset +0x1C
    // The third argument is the difference between pBegin address and a base at +0x1C
    compareResult = FUN_00636570(&LAB_006261e0, &pBegin, (int)pBegin - *(int*)(this + 0x1C));

    // Insert the new pair at the current end position
    pCurrent = *(int**)(this + 8);   // current begin pointer
    *pCurrent = 1;                   // new key (1)
    pCurrent[1] = (uint)(compareResult == 0);  // value based on comparison (0/1)

    // Advance begin pointer by 8 bytes (one element)
    *(int**)(this + 8) += 2;   // incremented by 2 ints (8 bytes)

    // Shift elements forward to make room for the new entry at the old end
    pOriginalEnd = *(int**)(this + 0xC);
    for (pShift = *(int**)(this + 8); pOriginalEnd < pShift; pShift -= 2) {
        pShift[0] = pShift[-2];   // copy key
        pShift[1] = pShift[-1];   // copy value
    }

    // Write the new pair at the old end position
    pShift = *(int**)(this + 8);
    *pOriginalEnd = *pShift;
    pOriginalEnd[1] = pShift[1];

    // Return the number of elements after insertion
    return (*(int*)(this + 8) - *(int*)(this + 0xC)) >> 3;
}
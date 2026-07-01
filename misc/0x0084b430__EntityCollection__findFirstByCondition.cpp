// FUNC_NAME: EntityCollection::findFirstByCondition
int __thiscall EntityCollection::findFirstByCondition(int this, int conditionParam) {
    int iResult;
    uint uiIndex;

    uiIndex = 0;
    if (*(int *)(this + 0x10) != 0) { // +0x10: count of elements in the collection
        do {
            iResult = evaluateCondition(conditionParam);
            if (iResult != 0) {
                return iResult; // Found a match, return handle/pointer
            }
            uiIndex = uiIndex + 1;
        } while (uiIndex < *(uint *)(this + 0x10));
    }
    return 0; // No match found
}
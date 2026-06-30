// FUNC_NAME: getAdjustedValue
int getAdjustedValue(void* objectPtr) {
    int* valuePtr = (int*)getGlobalTableEntry(objectPtr);
    if (*valuePtr != 0) {
        return *valuePtr + 8;
    }
    return 0;
}
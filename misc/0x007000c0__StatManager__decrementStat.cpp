// FUNC_NAME: StatManager::decrementStat
int __thiscall StatManager::decrementStat(int thisPtr, int index, int decrementValue) {
    // Array of ints at this+0x4
    int *statArray = (int *)(thisPtr + 4);
    statArray[index] -= decrementValue;
    // Dirty flag at this+0x1c
    *(byte *)(thisPtr + 0x1c) = 1;
    return statArray[index];
}
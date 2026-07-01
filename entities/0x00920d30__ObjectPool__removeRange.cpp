// FUNC_NAME: ObjectPool::removeRange
void __thiscall ObjectPool::removeRange(int* thisPtr, uint startIndex) {
    int* piVar1;
    int iVar2;

    if (startIndex < (uint)(thisPtr[1] - 1)) {
        do {
            piVar1 = (int*)(*thisPtr + startIndex * 8);
            if (piVar1 != piVar1 + 2) { // always true; maybe intended as piVar1[0] != piVar1[2]?
                iVar2 = piVar1[2];
                if (*piVar1 != iVar2) {
                    if (*piVar1 != 0) {
                        FUN_004daf90(piVar1);
                    }
                    *piVar1 = iVar2;
                    if (iVar2 != 0) {
                        piVar1[1] = *(int*)(iVar2 + 4);
                        *(int**)(iVar2 + 4) = piVar1;
                    }
                }
            }
            startIndex = startIndex + 1;
        } while (startIndex < thisPtr[1] - 1U);
    }
    thisPtr[1] = thisPtr[1] + -1;
    if (*(int*)(*thisPtr + thisPtr[1] * 8) == 0) {
        return;
    }
    FUN_004daf90();
    return;
}
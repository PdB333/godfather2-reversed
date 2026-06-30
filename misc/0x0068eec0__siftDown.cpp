// FUNC_NAME: siftDown
void __cdecl siftDown(int* array, int startIndex, int endIndex, int c, code* comparator) {
    int iVar1;
    char cVar2;
    int iVar3;
    int iVar4;

    iVar1 = startIndex * 2;
    iVar3 = startIndex;
    while (iVar4 = iVar1 + 2, iVar4 < endIndex) {
        cVar2 = (*comparator)(*(array + iVar4), *(array + iVar4 - 1));
        if (cVar2 != '\0') {
            iVar4 = iVar1 + 1;
        }
        *(array + iVar3) = *(array + iVar4);
        iVar3 = iVar4;
        iVar1 = iVar4 * 2;
    }
    if (iVar4 == endIndex) {
        *(array + iVar3) = *(array + endIndex - 1);
        iVar3 = endIndex + -1;
    }
    heapify(array, iVar3, startIndex, c, comparator); // FUN_0068e710
}
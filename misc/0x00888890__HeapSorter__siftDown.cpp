// FUNC_NAME: HeapSorter::siftDown
void HeapSorter::siftDown(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    int iVar1;
    int iVar2;
    int iVar3;
    int* puVar4;
    int* puVar5;
    
    iVar2 = param_4 * 2;
    while (iVar1 = iVar2 + 2, iVar1 < param_3) {
        // Compare keys at offset 0x08 within each 0x50-byte element
        if (*(uint *)(iVar1 * 0x50 + 8 + param_1) < *(uint *)(iVar1 * 0x50 + param_1 + -0x48)) {
            iVar1 = iVar2 + 1;
        }
        // Swap 0x50-byte elements (0x14 * 4 = 0x50)
        puVar4 = (int *)(iVar1 * 0x50 + param_1);
        puVar5 = (int *)(param_4 * 0x50 + param_1);
        for (iVar2 = 0x14; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar5 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar5 = puVar5 + 1;
        }
        param_4 = iVar1;
        iVar2 = iVar1 * 2;
    }
    if (iVar1 == param_3) {
        // Handle last element when heap size is odd
        puVar4 = (int *)(iVar1 * 0x50 + -0x50 + param_1);
        puVar5 = (int *)(param_4 * 0x50 + param_1);
        for (iVar3 = 0x14; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar5 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar5 = puVar5 + 1;
        }
        param_4 = iVar2 + 1;
    }
    // Recursive call to continue sifting down
    FUN_00887ad0(param_1, param_2, param_4, param_5, param_6);
    return;
}
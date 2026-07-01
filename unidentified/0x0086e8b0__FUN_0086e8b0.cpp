// FUNC_NAME: SomeManager::processPendingItems
void __fastcall SomeManager::processPendingItems(int thisPtr)
{
    bool bProcessed = false;
    char cHasMore;
    int iCurrentItem;
    undefined4 uVar4;
    int *piVar5;
    undefined4 uVar6;
    undefined1 auStack_24[4]; // unused? maybe iterator state
    undefined4 local_20; // iterator handle
    undefined4 local_1c;

    local_1c = 0;
    bProcessed = false;
    local_20 = 0;

    // Check if the list exists and is not disabled (bit 6 of flag at offset 0xC8)
    if (((*(int *)(thisPtr + 0x50) != 0) &&
         ((~(*(byte *)(*(int *)(thisPtr + 0x50) + 200) >> 6) & 1) != 0)) &&
        (*(int *)(thisPtr + 0x5c) != 0) &&
        (cHasMore = (**(code **)(**(int **)(thisPtr + 0x5c) + 0x1cc))(&local_20), cHasMore != '\0')) {
        do {
            iCurrentItem = (**(code **)(**(int **)(thisPtr + 0x5c) + 500))(&local_20);
            if (iCurrentItem != 0) {
                uVar6 = 0;
                uVar4 = FUN_006fbc40(0, 0); // allocate or get something
                FUN_007f96a0(0xc133c342, 5, uVar4, uVar6); // debug log with hash
                FUN_006fbc70(); // cleanup
                bProcessed = true;
            }
            cHasMore = (**(code **)(**(int **)(thisPtr + 0x5c) + 0x1d0))(auStack_24, auStack_24);
        } while ((cHasMore != '\0') && (!bProcessed));
    }

    // If iterator is null or its state (offset 0xf2c) is not 1, and global condition holds
    if (((*(int *)(thisPtr + 0x5c) == 0) || (*(int *)(*(int *)(thisPtr + 0x5c) + 0xf2c) != 1)) &&
        ((**(int **)(DAT_012233a0 + 4) != 0 && (**(int **)(DAT_012233a0 + 4) != 0x1f30)))) {
        piVar5 = (int *)FUN_0043b870(DAT_01130fa0); // get singleton
        (**(code **)(*piVar5 + 0x28))(0, 0, 0xffffffff, 0); // remove/delete with -1 index
    }
    return;
}
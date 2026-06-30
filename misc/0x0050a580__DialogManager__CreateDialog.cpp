// FUNC_NAME: DialogManager::CreateDialog
bool DialogManager::CreateDialog()
{
    int iVar1;
    undefined4 *puVar2;
    int parentList;
    undefined4 local_14;
    undefined4 local_10;
    undefined4 local_c;
    
    parentList = 0;
    iVar1 = getGlobalDialogManager(); // FUN_00421170
    if (iVar1 != 0) {
        parentList = *(int *)(iVar1 + 0x14); // +0x14: pointer to dialog list or container
    }
    iVar1 = 0;
    if (parentList != 0) {
        puVar2 = (undefined4 *)getGameHeapAllocator(); // FUN_009c8f80
        local_14 = 2;
        local_10 = 0x10;
        local_c = 0;
        // Allocate 0xA0 bytes with flags (likely size, alignment, pool)
        iVar1 = (**(code **)*puVar2)(0xa0, &local_14);
        if (iVar1 == 0) {
            return false;
        }
        dialogInitialize(iVar1); // FUN_0060ffd0 - construct default state
        *(undefined4 *)(iVar1 + 0x90) = 0; // +0x90: e.g., activeTimer
        *(undefined4 *)(iVar1 + 0x94) = 0; // +0x94: e.g., fadeState
        registerDialog(parentList, 0, 0, 0); // FUN_004bfc10 - add to parent's list
    }
    return iVar1 != 0;
}
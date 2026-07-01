// FUNC_NAME: SomeManager::processPendingActions
void __fastcall SomeManager::processPendingActions(int this)
{
    int iVar1;
    int iVar2;
    int iVar3;
    int local_18;
    undefined4 local_14;
    int local_10[3];
    
    FUN_004c23f0(0); // likely some initialization or lock
    iVar1 = *(int *)(this + 0x7c); // +0x7c: pointer to action list container
    if ((iVar1 != 0) && (iVar2 = 0, 0 < *(int *)(iVar1 + 0xc4))) { // +0xc4: count of actions
        do {
            iVar3 = *(int *)(*(int *)(iVar1 + 0xc0) + iVar2 * 4); // +0xc0: array of action pointers
            if ((iVar3 != 0) && (*(char *)(iVar3 + 0x10) + iVar3 != 0)) { // +0x10: some flag or vtable check
                FUN_004af8c0(local_10, 0x2001); // create/allocate something with ID 0x2001
                iVar3 = 0;
                if (local_10[0] != 0) {
                    iVar3 = local_10[0];
                }
                if (iVar3 != 0) {
                    local_18 = iVar3 + 0x48; // +0x48: offset to some sub-object
                    local_14 = 0;
                    if (local_18 != 0) {
                        local_14 = *(undefined4 *)(iVar3 + 0x4c); // +0x4c: previous pointer
                        *(int **)(iVar3 + 0x4c) = &local_18; // link into list
                    }
                    FUN_004b10d0(&local_18); // process the action
                    if (local_18 != 0) {
                        FUN_004daf90(&local_18); // cleanup/destroy
                    }
                }
            }
            iVar2 = iVar2 + 1;
        } while (iVar2 < *(int *)(iVar1 + 0xc4));
    }
    return;
}
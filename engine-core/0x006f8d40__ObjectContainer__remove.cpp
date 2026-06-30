// FUNC_NAME: ObjectContainer::remove
void __thiscall ObjectContainer::remove(int param_1, int param_2, char param_3)
{
    int iVar1;
    int iVar2;
    int iVar3;
    uint uVar4;
    int iVar5;
    int local_2c;
    int local_28;
    undefined1 local_24[4];
    undefined4 local_20;
    undefined4 local_1c;
    undefined1 local_18;
    undefined4 local_14;
    int local_10;
    undefined4 local_c;
    int local_8;
    undefined4 local_4;

    local_14 = 0;
    local_10 = 0;
    local_c = 0;
    local_8 = 0;
    local_4 = 0;

    // Temporarily modify the linked list to allow safe removal
    if ((param_2 != 0) && (param_2 + 0x48 != 0)) {
        local_4 = *(undefined4 *)(param_2 + 0x4c); // Save next pointer
        *(int **)(param_2 + 0x4c) = &local_8;     // Point next to stack dummy
        local_8 = param_2 + 0x48;                 // Dummy points to node content
    }

    local_2c = *(int *)(param_1 + 0x14); // Linked list head
    local_28 = param_1;                  // Save 'this'

    // Traverse linked list to find and remove node matching the dummy
    while (local_2c != 0) {
        if (*(int *)(local_2c + 0xc) == local_8) {
            FUN_006f89e0(local_2c);               // Unlink node from list
            FUN_006f83e0(local_24, &local_2c);    // Free node? (or adjust)
            param_1 = local_28;                    // Restore 'this'
        } else {
            local_2c = *(int *)(local_2c + 0x14); // next node
        }
    }

    iVar5 = 0;
    local_2c = 0;

    // If cleanup flag, iterate through dynamic array
    if ((param_3 != '\0') && (uVar4 = 0, *(int *)(param_1 + 0x30) != 0)) {
        do {
            iVar1 = *(int *)(param_1 + 0x2c);      // Array base
            iVar2 = *(int *)(iVar1 + iVar5);        // Entry pointer
            if (iVar2 == 0) {
                iVar3 = 0;
            } else {
                iVar3 = iVar2 + -0x48;              // Recover original pointer
            }
            if (iVar3 == param_2) {
                // Remove entry from array
                if ((iVar2 != 0) && (iVar2 != 0x48)) {
                    FUN_007376a0();                 // operator delete(iVar2?)
                }
                if (*(char *)(iVar1 + iVar5 + 8) != '\0') {
                    local_20 = DAT_0112aa84;
                    local_1c = 0;
                    local_18 = 0;
                    FUN_00408a00(&local_20, 0);     // Debug log
                }
                FUN_006f8490(uVar4);                // Shift array or free
            } else {
                uVar4 = uVar4 + 1;
                iVar5 = iVar5 + 0xc;
            }
        } while (uVar4 < *(uint *)(local_28 + 0x30));
    }

    // Clean up temporary modifications
    if (local_8 != 0) {
        FUN_004daf90(&local_8);     // Delete the dummy (or node)
    }
    if (local_10 != 0) {
        FUN_004daf90(&local_10);    // Delete other temporary (if any)
    }
    return;
}
// FUNC_NAME: ObjectManager::~ObjectManager
void __fastcall ObjectManager::~ObjectManager(undefined4 *this)
{
    int iVar1;
    int iVar2;
    int iVar3;
    undefined4 uVar4;
    undefined4 *puVar5;
    undefined4 *puVar6;
    int *piVar7;
    int iVar8;
    undefined4 uVar9;
    int unaff_FS_OFFSET;

    // Set vtable to base class vtable (destructor safety)
    *this = &PTR_FUN_00e36f74;

    // Clean up first list (offset +0x14: m_pSomeList, +0x18: m_someData)
    if (this[5] != 0) {
        iVar1 = **(int **)(unaff_FS_OFFSET + 0x2c);
        iVar8 = this[5];
        uVar9 = this[6];
        do {
            iVar2 = *(int *)(iVar1 + 8);
            iVar3 = *(int *)(iVar2 + iVar8);
            uVar4 = *(undefined4 *)(iVar2 + 4 + iVar8);
            cleanupSomeList(iVar8, uVar9);
            processSomeData();
            iVar8 = iVar3;
            uVar9 = uVar4;
        } while (iVar3 != 0);
    }

    // Destroy all objects in the doubly linked list (offset +0x10: m_pObjectList)
    puVar6 = (undefined4 *)this[4];
    while (puVar6 != (undefined4 *)0x0) {
        puVar5 = (undefined4 *)puVar6[0x31]; // next pointer at +0xC4
        if (puVar6 == (undefined4 *)this[4]) {
            this[4] = puVar5;
            if (puVar5 != (undefined4 *)0x0) {
                puVar5[0x32] = 0; // prev pointer at +0xC8
            }
        } else {
            if (puVar6[0x32] != 0) {
                *(undefined4 **)(puVar6[0x32] + 0xc4) = puVar5;
            }
            if (puVar6[0x31] != 0) {
                *(undefined4 *)(puVar6[0x31] + 200) = puVar6[0x32];
            }
        }
        // Call virtual destructor with argument 1 (delete)
        (**(code **)*puVar6)(1);
        puVar6 = puVar5;
    }

    // Free memory block (offset +0x0C: m_pMemoryBlock)
    iVar1 = this[3];
    if (iVar1 != 0) {
        piVar7 = (int *)getMemoryManager();
        (**(code **)(*piVar7 + 4))(iVar1, 0);
        this[3] = 0;
    }
    return;
}
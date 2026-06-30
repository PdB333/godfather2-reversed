// FUNC_NAME: HashContainer::~HashContainer

void __fastcall HashContainer::~HashContainer(HashContainer* this)
{
    int iVar1; // next node in list
    int iVar2; // current node
    uint uVar5; // bucket index
    int iVar3; // previous node in hash chain
    int iVar4; // current node in bucket walk

    uVar5 = g_initFlag & 1; // DAT_01223990 & 1
    this->vtable = &g_destroyedVtable; // PTR_FUN_00e3522c
    if (uVar5 == 0) {
        g_initFlag = g_initFlag | 1;
        HashContainer::staticInit(); // FUN_0049ca20
        _atexit(&HashContainer::staticCleanup); // LAB_00d50b90
    }
    iVar1 = this->listHead; // param_1[1] -> +0x04
    do {
        if (iVar1 == 0) {
            return;
        }
        iVar2 = this->listHead; // re-read? Actually param_1[1] unchanged in loop
        uVar5 = *(uint *)(iVar2 + 8) % g_bucketCount; // DAT_01223984
        iVar1 = *(int *)(iVar2 + 0x10); // nextList
        iVar3 = 0;
        // Walk hash chain to find and remove node
        for (iVar4 = *(int *)(g_buckets + uVar5 * 4); iVar4 != 0; iVar4 = *(int *)(iVar4 + 0x14)) {
            if (iVar4 == iVar2) {
                if (iVar3 == 0) {
                    *(undefined4 *)(g_buckets + uVar5 * 4) = *(undefined4 *)(iVar4 + 0x14);
                } else {
                    *(undefined4 *)(iVar3 + 0x14) = *(undefined4 *)(iVar4 + 0x14);
                }
                g_elementCount = g_elementCount - 1; // DAT_01223988
                break;
            }
            iVar3 = iVar4;
        }
        HashContainer::freeNode(iVar2); // FUN_009c8eb0
        this->listHead = iVar1;
    } while( true );
}
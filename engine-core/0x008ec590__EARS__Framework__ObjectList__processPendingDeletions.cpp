// FUNC_NAME: EARS::Framework::ObjectList::processPendingDeletions
void __fastcall ObjectList::processPendingDeletions(int this) // 0x008ec590
{
    int iVar1;
    int iVar2;
    undefined4 *puVar3;
    int *piVar4;

    FUN_008eb9c0(); // likely lockMutex or enterCriticalSection
    iVar1 = **(int **)(this + 0x10); // +0x10: head of pending deletion list
    do {
        iVar2 = *(int *)(this + 0x10); // +0x10: current list head
        if (this == -0xc) {
            FUN_00b97aea(); // assert or error handler
        }
        if (iVar1 == iVar2) {
            return;
        }
        if (this == -0xc) {
            FUN_00b97aea(); // assert or error handler
        }
        if (iVar1 == *(int *)(this + 0x10)) {
            FUN_00b97aea(); // assert or error handler
        }
        while( true ) {
            puVar3 = *(undefined4 **)(iVar1 + 0x10); // +0x10: next pointer in node
            *(undefined4 **)(iVar1 + 0x20) = puVar3; // +0x20: some temporary pointer
            if (puVar3 == (undefined4 *)0x0) break;
            piVar4 = (int *)puVar3[2]; // +0x08: some data pointer
            *(undefined4 *)(iVar1 + 0x20) = *puVar3; // copy first field
            if (piVar4 == (int *)0x0) break;
            (**(code **)(*piVar4 + 0xc))(); // call virtual function at vtable+0xc
            FUN_004087c0(piVar4 + 0xf); // likely free or release memory
        }
        FUN_008ea1d0(); // advance to next node or process next
    } while( true );
}
// FUNC_NAME: SomeClass::buildSortedListFromLinkedList
void* FUN_005f79a0(int param_1, int param_2, int* param_3)
{
    byte bVar1;
    int iVar2;
    bool bVar3;
    int* piVar4;
    void* _Dst;
    int* piVar5;
    int iVar6;
    int* piVar7;
    int unaff_retaddr;
    int iStack_20;
    int iStack_1c;
    int iStack_18;
    undefined4 local_c;
    undefined4 local_8;
    undefined4 local_4;
    
    piVar7 = *(int**)(param_2 + 0x34); // +0x34: linked list head pointer
    bVar1 = *(byte*)(param_2 + 0x38); // +0x38: flags byte
    *param_3 = 0;
    if ((bVar1 & 8) == 0) {
        if (piVar7 != (int*)0x0) {
            iVar6 = 0;
            piVar4 = piVar7;
            do {
                piVar4 = (int*)*piVar4; // traverse linked list via first field (next pointer)
                iVar6 = iVar6 + 1;
            } while (piVar4 != (int*)0x0);
            *param_3 = iVar6; // store count
        }
    }
    else {
        *param_3 = 2; // special case: flag bit 3 set means fixed size 2
    }
    iVar6 = *param_3;
    local_c = 0;
    local_8 = 0;
    local_4 = 0;
    _Dst = (void*)(**(code**)**(undefined4**)(param_1 + 0x10))(iVar6 * 0xc, &local_c); // +0x10: allocator function pointer, allocates iVar6 * 12 bytes
    _memset(_Dst, 0, iVar6 * 0xc);
    if (_Dst != (void*)0x0) {
        if ((*(byte*)(unaff_retaddr + 0x38) & 8) == 0) {
            iVar6 = *param_3 + -1;
            bVar3 = false;
            piVar4 = (int*)((int)_Dst + iVar6 * 0xc);
            do {
                if (iVar6 < 0) {
                    if (!bVar3) {
                        return _Dst;
                    }
                    break;
                }
                piVar5 = (int*)(*(int*)(unaff_retaddr + 0x24) + (uint)*(byte*)((int)piVar7 + 0xb) * 0xc); // +0x24: some lookup table base, +0xb: index into table
                iVar2 = *piVar5;
                if (iVar2 == 0) {
                    bVar3 = true;
                }
                else {
                    iStack_18 = *(int*)(iVar2 + 0x20) + (((int)piVar7 - piVar5[2]) / 0xc) * 0x24; // +0x20: offset field, compute array index
                    iStack_1c = *(int*)(iVar2 + 4); // +0x04: next pointer in some list
                    *(int**)(iVar2 + 4) = &iStack_20;
                    iStack_20 = iVar2;
                    if ((piVar4 != &iStack_20) && (*piVar4 != iVar2)) {
                        if (*piVar4 != 0) {
                            FUN_004daf90(piVar4); // likely a destructor/free for the slot
                        }
                        *piVar4 = iVar2;
                        if (iVar2 != 0) {
                            piVar4[1] = *(int*)(iVar2 + 4);
                            *(int**)(iVar2 + 4) = piVar4;
                        }
                    }
                    piVar4[2] = iStack_18; // store computed offset
                    if (iStack_20 != 0) {
                        piVar5 = *(int**)(iStack_20 + 4);
                        if (piVar5 == &iStack_20) {
                            *(int*)(iStack_20 + 4) = iStack_1c;
                            piVar7 = (int*)*piVar7;
                            goto LAB_005f7b1d;
                        }
                        if ((int*)piVar5[1] != &iStack_20) {
                            do {
                                piVar5 = (int*)piVar5[1];
                            } while ((int*)piVar5[1] != &iStack_20);
                        }
                        piVar5[1] = iStack_1c;
                    }
                    piVar7 = (int*)*piVar7;
                }
LAB_005f7b1d:
                iVar6 = iVar6 + -1;
                piVar4 = piVar4 + -3;
            } while (!bVar3);
            FUN_005f7e50(local_4, _Dst); // error handling / cleanup
            return (void*)0x0;
        }
        FUN_005f7ba0(unaff_retaddr + 8); // likely a cleanup function for special case
        FUN_005f7ba0(unaff_retaddr + 0x14);
    }
    return _Dst;
}
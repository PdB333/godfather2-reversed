// FUNC_NAME: ResourceSlot::setFromDescriptor
void __thiscall ResourceSlot::setFromDescriptor(void* this, int* pDesc) {
    int* piVar1; // pointer to m_pData field
    int iVar2;
    char cVar3;
    int* piVar4; // saved pDesc
    int unaff_EBX;
    int* piVar5; // pointer to sub-field in pDesc

    piVar4 = pDesc;
    piVar1 = (int*)((char*)this + 4); // +0x4: m_pData

    if (pDesc == (int*)0x0) {
        piVar5 = (int*)0x0;
    } else {
        piVar5 = pDesc + 0x12; // +0x48: field at offset 0x48 in descriptor
    }

    // Compare and swap m_pData with the descriptor's internal pointer
    if ((int*)*piVar1 != piVar5) {
        if ((int*)*piVar1 != (int*)0x0) {
            FUN_004daf90(piVar1); // free old m_pData
        }
        *piVar1 = (int)piVar5;
        if (piVar5 != (int*)0x0) {
            *(int*)((char*)this + 8) = piVar5[1]; // +0x8: m_pPrev or link
            piVar5[1] = (int)piVar1;
        }
    }

    pDesc = (int*)0x0; // local var, used as out parameter for virtual call
    // Virtual call on descriptor's vtable (+0x10) to resolve hash 0x55859efa
    cVar3 = (**(code**)(*piVar4 + 0x10))(0x55859efa, &pDesc);
    if ((cVar3 != '\0') && (unaff_EBX != 0)) {
        *(char*)((char*)this + 0xc) = 1; // +0xc: m_bValid
        piVar4 = (int*)FUN_007ffdf0(); // get global table
        piVar1 = (int*)((char*)this + 0x10); // +0x10: m_pGlobalData

        if (piVar1 != piVar4) {
            iVar2 = *piVar4;
            if (*piVar1 != iVar2) {
                if (*piVar1 != 0) {
                    FUN_004daf90(piVar1);
                }
                *piVar1 = iVar2;
                if (iVar2 != 0) {
                    *(int*)((char*)this + 0x14) = *(int*)(iVar2 + 4); // +0x14: link
                    *(int**)(iVar2 + 4) = piVar1;
                }
            }
        }
        *(int*)((char*)this + 0x18) = piVar4[2]; // +0x18: index or extra data
        return;
    }
    *(char*)((char*)this + 0xc) = 0; // invalidate
    return;
}
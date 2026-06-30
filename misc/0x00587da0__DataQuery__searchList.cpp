// FUNC_NAME: DataQuery::searchList
int __thiscall DataQuery::searchList(DataQuery *this) {
    float fVar1;
    int iVar2;
    undefined4 uVar3;
    char cVar4;
    ListEntry *pEntry;
    int iVar6;
    char *pcVar7;
    int iVar8;
    uint uFlag;
    float fVar10;
    float fVar11;
    float fVar12;
    int local_10;
    undefined4 local_c;
    undefined1 local_8;
    undefined4 local_4;

    // Dereference this->pBaseObject (offset 0) -> +0x70 -> +0x2c to get some ID
    iVar2 = *(int *)(*(int *)(*this->pBaseObjRef + 0x70) + 0x2c);
    if (iVar2 != 0) {
        // If some flag is set, call a reset function
        if (*(char *)(iVar2 + 0x10) != '\0') {
            FUN_005878e0(); // likely resetData
        }
        uVar3 = *(undefined4 *)(iVar2 + 8); // some resource handle
        iVar2 = this->pTargetData[0x14 / 4]; // offset +0x14
        FUN_00588070(uVar3, 0xffffffff); // releaseResource ? 
        FUN_00588070(uVar3, iVar2);
        // Get iterator for list (FUN_00587fc0 returns first entry or next)
        pEntry = (ListEntry *)FUN_00587fc0();
        while (pEntry != (ListEntry *)0x0) {
            uFlag = pEntry->flags & 0x20; // bit 5: alternate fields?
            if ((uFlag == 0) || (pEntry->size < 2)) {
                iVar6 = pEntry->field1;    // offset 4
                iVar8 = pEntry->size;      // offset 0
            } else {
                iVar6 = pEntry->altField1; // offset 8
                iVar8 = pEntry->size;      // still size from offset 0
            }
            // Check if field matches target ID from pTargetData+0x14
            if ((iVar6 == -1) || (iVar6 == iVar2)) {
                fVar1 = *(float *)(this->pTargetData + 0x1c); // offset +0x1c (range min)
                if ((uFlag == 0) || (iVar8 < 2)) {
                    fVar12 = (float)pEntry->rangeMin;   // offset 4 (used as float)
                    fVar11 = (float)pEntry->rangeMax;   // offset 8 (used as float)
                } else {
                    fVar12 = (float)pEntry->altRangeMin; // offset 12
                    fVar11 = (float)pEntry->altRangeMax; // offset 16
                }
                // If flag bit 3 is set, scale range values by some delta
                if ((pEntry->flags >> 3 & 1) != 0) {
                    fVar10 = *(float *)(this->pTargetData + 0x24) - DAT_00e2b1a4; // global delta
                    fVar12 = fVar10 * fVar12;
                    fVar11 = fVar10 * fVar11;
                }
                // Check if fVar1 is within [fVar12, fVar11]
                if ((fVar12 <= fVar1) && (fVar1 <= fVar11)) {
                    // Determine ID2 based on flag/size
                    if ((uFlag == 0) || (iVar8 < 2)) {
                        if ((pEntry->subType == 1) && (pEntry->pData != (int *)0x0)) {
                            iVar6 = *pEntry->pData; // dereference if not null
                        } else {
                            iVar6 = 0;
                        }
                    } else {
                        iVar6 = pEntry->altField2; // offset 8? Wait, already used. Actually offset 8 is altField1, but they use piVar5[2] which is offset 8. So altField1 used as ID? Better: piVar5[2] in the else branch is used as iVar6. So pEntry->field3?
                        // Actually the decompile: iVar6 = piVar5[2] in the else branch of that second if. So we need another field.
                    }
                    // Check if iVar6 matches this->idA (param_1[2])
                    if (iVar6 == this->idA) {
                        if ((uFlag == 0) || (iVar8 < 2)) {
                            if ((pEntry->subType == 1) && (pEntry->pData != 0)) {
                                iVar6 = *(int *)(pEntry->pData + 4); // offset +4 from pData
                            } else {
                                iVar6 = 0;
                            }
                        } else {
                            iVar6 = pEntry->field8; // offset 32? piVar5[8]
                        }
                        if (iVar6 == this->idC) {
                            // Get string pointer
                            if ((uFlag == 0) || (iVar8 < 2)) {
                                pcVar7 = (char *)pEntry->pString; // offset 16 (piVar5[4])
                            } else {
                                pcVar7 = (char *)pEntry->altString; // offset 24 (piVar5[6])
                            }
                            if (pcVar7 == (char *)0x0) {
                                goto LAB_SET_RESULT;
                            }
                            local_10 = (int)this->pBaseObjRef; // store base pointer
                            local_c = 0xfffffffb;
                            local_8 = 0;
                            local_4 = 0;
                            // Call function from table based on first char of string
                            if ((*pcVar7 < '\n') &&
                                (cVar4 = (*(code *)(&PTR_FUN_0103af90)[*pcVar7])(&local_10), cVar4 != '\0'))
                            {
LAB_SET_RESULT:
                                this->pResult = (int)pEntry;
                                // If flag has bit 5 set and size > 3, return a different value
                                if (((pEntry->flags & 0x20) != 0) && (3 < pEntry->size)) {
                                    return pEntry->field5; // offset 20
                                }
                                return 0;
                            }
                        }
                    }
                }
            }
            pEntry = (ListEntry *)FUN_00587fc0(); // next entry
        }
    }
    return -1;
}
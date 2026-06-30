// FUNC_NAME: SceneManager::processObjects
void __thiscall SceneManager::processObjects(SceneManager* thisPtr, undefined4 param_2, undefined4 param_3, int* pCallbackVtable, int bFlagInsert, undefined4 param_6, char bUseFilteredEnum, char bSkipCheck)
{
    undefined4* pSmartPtr;
    char cAllow;
    int* pNode;
    int iCount;
    int iIndex;
    undefined4** ppEntry;
    int iTemp1;
    int iTemp2;
    int* pListHead;
    int iEnumCount;
    int aiStackBuf[2];
    undefined4 local_2b0;
    short sRefCount; // +0x02 from smart pointer? actually at +0x02 and +0x06?
    short sUnknown;  // +0x04
    undefined** ppEnumManager;
    undefined1 uEnumResult; // unused? actually used as byte
    undefined1* pCurEntry;
    int iEnumIdx;
    int iEnumCount2;
    undefined1 local_27c[256];
    undefined1* pEnumArray;
    int iEnumTotal;
    undefined4 uEnumFlags;
    undefined1 auStackBuf[64];
    undefined** ppDtor;
    undefined4 local_f0;
    undefined4 local_ec;
    undefined4 local_e8;
    undefined4 local_e4;
    undefined4* local_70[7];
    undefined4 local_54;
    
    lockMutex(param_2);
    initSomeGlobal();
    
    // Smart pointer refcount management on local_70[0]
    if (local_70[0] != &local_2b0) {
        if (((local_70[0] != (undefined4 *)0x0) && 
             (*(short *)((int)local_70[0] + 2) != 0)) &&
            (*(short *)((int)local_70[0] + 6) = *(short *)((int)local_70[0] + 6) - 1,
             *(short *)((int)local_70[0] + 6) == 0)) {
            (**(code **)*local_70[0])(1);
        }
        local_70[0] = &local_2b0;
        if (local_2ac != 0) {
            local_2aa = local_2aa + 1;
        }
    }
    
    // Save four dwords from thisPtr (likely frustum or query data)
    local_f0 = thisPtr[0];
    local_ec = thisPtr[1];
    local_e8 = thisPtr[2];
    local_e4 = thisPtr[3];
    
    pCurEntry = local_27c;
    local_54 = param_3;
    
    if (bUseFilteredEnum == 0) {
        // Standard enumeration (all objects)
        iEnumCount2 = -0x7ffffff0;
        uEnumFlags = 0x80000010;
        iIndex = 0;
        pEnumArray = auStackBuf;
        iEnumIdx = 0;
        ppEnumManager = &PTR_FUN_00e35734; // Enumeration manager for all objects
        iEnumTotal = 0;
        uEnumResult = 0;
        FUN_009eb910(local_70, *(undefined4*)(*(int*)(DAT_01223480 + 0x24) + 0x6c), &ppEnumManager);
        
        if (0 < iEnumTotal) {
            do {
                if ((bSkipCheck == 0) ||
                    (cAllow = (**(code**)(*pListHead + 0xc))
                                 (thisPtr, *(undefined4*)(pEnumArray + iIndex * 4), 0, param_6),
                     cAllow != 0)) {
                    if (bFlagInsert == 0) {
                        if (pCallbackVtable != (int*)0x0) {
                            (**(code**)(*pCallbackVtable + 4))(*(undefined4*)(pEnumArray + iIndex * 4), 0);
                        }
                    } else {
                        if (*(int*)(pEnumArray + iIndex * 4) == 0) {
                            iTemp1 = 0;
                        } else {
                            iTemp1 = *(int*)(pEnumArray + iIndex * 4) + 0x48;
                        }
                        iTemp2 = 0;
                        if (iTemp1 != 0) {
                            iTemp2 = *(int*)(iTemp1 + 4);
                            *(int**)(iTemp1 + 4) = &iTemp1;
                        }
                        FUN_004b10d0(&iTemp1);
                        if (iTemp1 != 0) {
                            pNode = *(int**)(iTemp1 + 4);
                            if (pNode == &iTemp1) {
                                *(int*)(iTemp1 + 4) = iTemp2;
                            } else {
                                if ((int*)pNode[1] != &iTemp1) {
                                    do {
                                        pNode = (int*)pNode[1];
                                    } while ((int*)pNode[1] != &iTemp1);
                                }
                                pNode[1] = iTemp2;
                            }
                        }
                    }
                }
                iIndex = iIndex + 1;
            } while (iIndex < iEnumTotal);
        }
        FUN_004b0580();
    } else {
        // Filtered enumeration (with type filter)
        iIndex = 0;
        ppEnumManager = &PTR_LAB_00e3572c; // different enumeration manager (filtered)
        iEnumCount2 = -0x7ffffff0;
        iEnumIdx = 0;
        uEnumResult = 0;
        FUN_009eb910(local_70, *(undefined4*)(*(int*)(DAT_01223480 + 0x24) + 0x6c), &ppEnumManager);
        
        iEnumCount = 0;
        if (0 < iEnumIdx) {
            do {
                ppEntry = *(undefined4***)(pCurEntry + iIndex + 8);
                if (local_70 == ppEntry) {
                    ppEntry = *(undefined4***)(pCurEntry + iIndex);
                }
                if ((ppEntry != (undefined4**)0x0) && ((int)*(char*)(ppEntry + 4) + (int)ppEntry != 0)) {
                    FUN_004af8c0(aiStackBuf, 0x2001);
                    iEnumTotal = 0;
                    if (aiStackBuf[0] != 0) {
                        iEnumTotal = aiStackBuf[0];
                    }
                    if ((iEnumTotal != 0) &&
                       ((bSkipCheck == 0 ||
                        (cAllow = (**(code**)(*pListHead + 0xc))(thisPtr, iEnumTotal, ppEntry, param_6),
                         cAllow != 0)))) {
                        if (bFlagInsert == 0) {
                            if (pCallbackVtable != (int*)0x0) {
                                (**(code**)(*pCallbackVtable + 4))(iEnumTotal, ppEntry);
                            }
                        } else {
                            iTemp1 = iEnumTotal + 0x48;
                            iTemp2 = 0;
                            if (iTemp1 != 0) {
                                iTemp2 = *(int*)(iEnumTotal + 0x4c);
                                *(int**)(iEnumTotal + 0x4c) = &iTemp1;
                            }
                            FUN_004b10d0(&iTemp1);
                            if (iTemp1 != 0) {
                                pNode = *(int**)(iTemp1 + 4);
                                if (pNode == &iTemp1) {
                                    *(int*)(iTemp1 + 4) = iTemp2;
                                } else {
                                    if ((int*)pNode[1] != &iTemp1) {
                                        do {
                                            pNode = (int*)pNode[1];
                                        } while ((int*)pNode[1] != &iTemp1);
                                    }
                                    pNode[1] = iTemp2;
                                }
                            }
                        }
                    }
                }
                iEnumCount = iEnumCount + 1;
                iIndex = iIndex + 0x10;
            } while (iEnumCount < iEnumIdx);
        }
        
        iIndex = iEnumCount2;
        ppEnumManager = &PTR_LAB_00e3572c;
        if (-1 < iEnumCount2) {
            TlsGetValue(DAT_01139810);
            FUN_00aa26e0(pCurEntry, iIndex << 4, 0x17);
        }
    }
    
    pSmartPtr = local_70[0];
    ppDtor = &PTR_FUN_00e39bc8;
    if (((local_70[0] != (undefined4*)0x0) && (*(short*)(local_70[0] + 2) != 0)) &&
        (*(short*)((int)local_70[0] + 6) = *(short*)((int)local_70[0] + 6) - 1,
         *(short*)((int)pSmartPtr + 6) == 0)) {
        (**(code**)*pSmartPtr)(1);
    }
    return;
}
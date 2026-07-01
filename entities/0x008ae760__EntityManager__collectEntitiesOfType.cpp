// FUNC_NAME: EntityManager::collectEntitiesOfType
int* __thiscall EntityManager::collectEntitiesOfType(int thisPtr, int* outArray, char includeInactive)
{
    int* entityList;
    int entityCount;
    int currentEntity;
    int* arraySlot;
    int iVar2;
    int iVar3;

    outArray[0] = 0;  // array pointer
    outArray[1] = 0;  // count
    outArray[2] = 0;  // capacity

    entityList = *(int*)(thisPtr + 0x60);  // +0x60: entity list head
    if (entityList != 0) {
        if (*(int*)(entityList + 8) == 0) {
            entityList = 0;
        }
        while (entityList != 0) {
            if ((includeInactive != '\0') ||
               (iVar2 = (*(code *)PTR_FUN_00e35c28)(), (*(uint*)(iVar2 + 0x30) >> 1 & 1) == 0)) {
                iVar3 = (*(code *)PTR_FUN_00e35c28)();
                iVar2 = outArray[2];
                if (outArray[1] == iVar2) {
                    if (iVar2 == 0) {
                        iVar2 = 1;
                    } else {
                        iVar2 = iVar2 * 2;
                    }
                    FUN_00486800(iVar2);  // reallocate array
                }
                arraySlot = (undefined4*)(*outArray + outArray[1] * 4);
                outArray[1] = outArray[1] + 1;
                if (arraySlot != (undefined4*)0x0) {
                    *arraySlot = *(undefined4*)(iVar3 + 8);  // copy entity ID
                }
            }
            (*_UNK_00e35c2c)();  // advance to next entity in list
        }
        if (1 < (uint)outArray[1]) {
            _qsort((void*)*outArray, outArray[1], 4, (_PtFuncCompare*)&LAB_008aab50);  // sort by entity ID
        }
    }
    return outArray;
}
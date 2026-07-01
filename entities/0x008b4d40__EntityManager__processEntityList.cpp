//FUNC_NAME: EntityManager::processEntityList
void __fastcall EntityManager::processEntityList(int thisPtr)
{
    int iVar1;
    char cVar2;
    int iVar3;
    int local_4;

    // Check global manager validity, game state, and entity flag
    if ( (*(int *)(DAT_01223484 + 8) == 0) ||
         (local_4 = thisPtr, cVar2 = FUN_00481620(), cVar2 == '\0') ||
         (*(int *)(thisPtr + 0x1a8) == 0) ) {
        return;
    }

    // Transform thisPtr into a list head (likely linked list of entities)
    FUN_008b4020(&local_4);

    iVar3 = DAT_01223484;
    for (iVar1 = local_4; iVar1 != 0; iVar1 = **(int **)(iVar1 + 0x14)) {
        if (*(int *)(iVar3 + 0x30) != 0) {
            // Call method from vtable at global+0x30, offset +8
            (**(code **)(**(int **)(iVar3 + 0x30) + 8))(*(undefined4 *)(iVar1 + 4));
            iVar3 = DAT_01223484;
        }
        if (iVar1 == 0) break;
    }

    FUN_008b41b0();
    return;
}
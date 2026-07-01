// FUNC_NAME: SomeClass::processSomeList
void __fastcall SomeClass::processSomeList(int thisPtr)
{
    undefined4 uVar1;
    bool bVar2;
    int iVar3;
    undefined *puVar4;
    int local_c;
    int local_8;
    int *local_4;

    // Get some value from a lookup table using offset 0x58 from this
    uVar1 = *(undefined4 *)(&DAT_00002494 + *(int *)(thisPtr + 0x58));
    bVar2 = false;
    local_c = 0;
    local_8 = 0;
    local_4 = (int *)0x0;
    do {
        iVar3 = FUN_00424c90(uVar1);
        if (iVar3 == 4) {
            return;
        }
        if (bVar2) {
            local_c = FUN_00425030(uVar1, &local_4, &local_c);
            if (local_8 == local_c) {
                return;
            }
        }
        else {
            local_c = FUN_00425030(uVar1, &local_4, 0);
            bVar2 = true;
            local_8 = local_c;
        }
    } while ((local_4 == (int *)0x0) ||
            (puVar4 = (undefined *)(**(code **)(*local_4 + 0x10))(), puVar4 != &DAT_00e078fa));
    FUN_006d67f0();
    return;
}
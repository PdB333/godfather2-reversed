// FUNC_NAME: SomeClass::updateAnimationOrState
void __fastcall SomeClass::updateAnimationOrState(int this)
{
    undefined4 uVar1;
    undefined4 uVar2;
    int iVar3;
    int iVar4;
    undefined4 *puVar5;
    undefined4 *puVar6;

    if (*(int *)(this + 0x10) == 0) {
        return;
    }
    if (*(char *)(this + 0x170) == '\0') {
        iVar3 = FUN_004ee450(this + 0x10); // likely getAnimationState or similar
        if (((iVar3 != 0) && (iVar3 = FUN_004ee3a0(this + 0x10, 0), uVar2 = _DAT_00d5780c, iVar3 != 0)) && (*(undefined4 **)(iVar3 + 0x24) != (undefined4 *)0x0)) {
            uVar1 = *(undefined4 *)(this + 0x30);
            puVar5 = *(undefined4 **)(iVar3 + 0x24);
            puVar6 = (undefined4 *)(this + 0xd8);
            for (iVar4 = 0x26; iVar4 != 0; iVar4 = iVar4 + -1) {
                *puVar6 = *puVar5;
                puVar5 = puVar5 + 1;
                puVar6 = puVar6 + 1;
            }
            *(undefined4 *)(this + 0xf8) = uVar1;
            *(undefined4 *)(this + 0xfc) = *(undefined4 *)(this + 0x34);
            *(undefined4 *)(this + 0x100) = *(undefined4 *)(this + 0x38);
            *(undefined4 *)(this + 0x120) = uVar2;
            *(undefined4 *)(this + 0xe8) = DAT_00d5f208;
            uVar2 = DAT_00d5ef90;
            *(undefined4 *)(this + 0xdc) = 0x2d2307a5;
            *(undefined2 *)(this + 0x104) = 0x81;
            *(undefined4 *)(this + 0x118) = uVar2;
            FUN_004ee5a0((undefined4 *)(this + 0xd8)); // likely applyAnimationData
            *(undefined1 *)(this + 0x170) = 1;
        }
        if (*(char *)(this + 0x170) == '\0') {
            return;
        }
    }
    FUN_004df870(&DAT_00e543b0); // likely render or update something
    FUN_004df6e0(); // likely another update call
    return;
}
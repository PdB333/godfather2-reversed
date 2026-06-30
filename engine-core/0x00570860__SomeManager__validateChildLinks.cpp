// FUNC_NAME: SomeManager::validateChildLinks
void __thiscall SomeManager::validateChildLinks(void)
{
    int iVar1;
    uint uVar2;
    undefined4 uVar3;
    int iVar4;

    if (this != 0) {
        uVar3 = 0;
        if ((*(int *)(this + 0x1c) != 0) && (0 < *(int *)(this + 0x3c))) {
            uVar3 = *(undefined4 *)(this + 0x40);
        }
        iVar4 = 0;
        if (0 < *(int *)(this + 0x2c)) {
            do {
                iVar1 = *(int *)(*(int *)(this + 0x30) + iVar4 * 4);
                uVar2 = *(uint *)(iVar1 + 4) & 0xff;
                if (uVar2 < 10) {
                    if (*(int *)(iVar1 + 0x24) != 0) {
                        return;
                    }
                    *(int *)(iVar1 + 0x24) = iVar1 + 0x30;
                }
                else {
                    if (*(int *)(iVar1 + 0x2c) != 0) {
                        return;
                    }
                    *(int *)(iVar1 + 0x2c) = iVar1 + 0x40;
                }
                if (uVar2 < 10) {
                    uVar2 = *(uint *)(iVar1 + 0x20);
                }
                else {
                    uVar2 = *(uint *)(iVar1 + 0x28);
                }
                if ((uVar2 & 0xfffffff) == 0) {
                    FUN_00580ec0(uVar3);
                }
                iVar4 = iVar4 + 1;
            } while (iVar4 < *(int *)(this + 0x2c));
        }
    }
    return;
}
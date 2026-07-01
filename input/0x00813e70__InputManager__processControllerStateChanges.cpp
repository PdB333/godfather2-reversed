// FUNC_NAME: InputManager::processControllerStateChanges
void __fastcall InputManager::processControllerStateChanges(int thisPtr)
{
    ushort uVar1;
    undefined4 uVar2;
    int iVar3;
    int iVar4;
    ushort uVar5;
    undefined4 local_4;
    
    local_4 = 0;
    if (*(int *)(thisPtr + 0xc) != 0) {
        do {
            iVar3 = *(int *)(thisPtr + 8);
            uVar2 = *(undefined4 *)(iVar3 + local_4 * 8);
            iVar4 = iVar3 + local_4 * 8;
            uVar1 = *(ushort *)(iVar4 + 4);
            uVar5 = *(ushort *)(iVar3 + 6 + local_4 * 8) | uVar1;
            uVar5 = -uVar5 & uVar5;
            if ((uVar1 & uVar5) != 0) {
                iVar3 = FUN_00405720(uVar2,0);
                if (iVar3 == 0) {
                    FUN_00447b50(uVar2,1);
                }
                else {
                    FUN_00406280(uVar2,1);
                }
            }
            if ((*(ushort *)(iVar4 + 6) & uVar5) != 0) {
                iVar4 = FUN_00405720(uVar2,0);
                if (iVar4 == 0) {
                    FUN_00447b50(uVar2,1);
                }
                else {
                    FUN_00406280(uVar2,0);
                }
            }
            local_4 = local_4 + 1;
        } while (local_4 < *(uint *)(thisPtr + 0xc));
    }
    *(undefined4 *)(thisPtr + 0xc) = 0;
    FUN_009c8f10(*(undefined4 *)(thisPtr + 8));
    *(undefined4 *)(thisPtr + 8) = 0;
    *(undefined4 *)(thisPtr + 0x10) = 0;
    return;
}
// FUNC_NAME: NetConnection::processDirtyFlags
uint __fastcall NetConnection::processDirtyFlags(int this)
{
    byte bVar1;
    uint in_EAX;
    uint uVar2;
    int iVar3;
    ushort uVar5;
    int iVar4;
    
    uVar5 = 0;
    uVar2 = in_EAX & 0xffffff00;
    if (*(short *)(this + 0x60) != 0) {
        // Check dirty flag bit 0 (field at +0x64)
        if (((*(byte *)(this + 0x60) & 1) != 0) &&
           ((uint)*(ushort *)(*(int *)(this + 0x78) + 0x10) != *(uint *)(this + 100))) {
            uVar5 = 1;
            *(undefined2 *)(*(int *)(this + 0x78) + 0x10) = *(undefined2 *)(this + 100);
        }
        // Check dirty flag bit 1 (field at +0x68)
        if (((*(byte *)(this + 0x60) >> 1 & 1) != 0) &&
           ((uint)*(ushort *)(*(int *)(this + 0x78) + 0x12) != *(uint *)(this + 0x68))) {
            uVar5 = uVar5 | 2;
            *(undefined2 *)(*(int *)(this + 0x78) + 0x12) = *(undefined2 *)(this + 0x68);
        }
        // Check dirty flag bit 2 (field at +0x6c, pointer to some object)
        if (((((*(byte *)(this + 0x60) >> 2 & 1) != 0) && (*(int *)(this + 0x6c) == 0)) &&
            (iVar4 = *(int *)(this + 0x78), iVar3 = 0, *(int *)(iVar4 + 0xc) != 0)) ||
           ((iVar3 = *(int *)(this + 0x6c), iVar3 != 0 &&
            (iVar4 = *(int *)(this + 0x78), *(int *)(iVar4 + 0xc) == 0)))) {
            uVar5 = uVar5 | 4;
            if (iVar3 == 0) {
                iVar3 = 0;
            }
            else {
                iVar3 = iVar3 + DAT_01205224;
            }
            *(int *)(iVar4 + 0xc) = iVar3;
        }
        // Check dirty flag bit 3 (field at +0x70)
        if ((*(byte *)(this + 0x60) >> 3 & 1) != 0) {
            iVar3 = *(int *)(this + 0x78);
            if ((uint)*(ushort *)(iVar3 + 0x14) != *(uint *)(this + 0x70)) {
                uVar5 = uVar5 | 8;
                *(short *)(iVar3 + 0x14) = (short)*(uint *)(this + 0x70);
            }
        }
        bVar1 = *(byte *)(this + 0x60) >> 4;
        iVar4 = CONCAT31((int3)((uint)iVar3 >> 8),bVar1);
        // Check dirty flag bit 4 (field at +0x74)
        if ((bVar1 & 1) != 0) {
            iVar4 = *(int *)(this + 0x78);
            if (*(int *)(iVar4 + 0x18) != *(int *)(this + 0x74)) {
                uVar5 = uVar5 | 0x10;
                *(int *)(iVar4 + 0x18) = *(int *)(this + 0x74);
            }
        }
        // Clear dirty flags and pending values
        *(undefined2 *)(this + 0x60) = 0;
        uVar2 = CONCAT31((int3)((uint)iVar4 >> 8),(*(ushort *)(this + 0x62) & uVar5) != 0);
        *(undefined2 *)(this + 0x62) = 0;
        *(undefined4 *)(this + 0x74) = 0;
        *(undefined4 *)(this + 0x70) = 0;
        *(undefined4 *)(this + 0x6c) = 0;
        *(undefined4 *)(this + 0x68) = 0;
        *(undefined4 *)(this + 100) = 0;
    }
    return uVar2;
}
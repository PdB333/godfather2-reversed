// FUNC_NAME: Player::setVisibilityOrSomething
void __thiscall Player::setVisibilityOrSomething(int *this, byte param_2)
{
  int iVar1;
  undefined4 uVar2;
  code *pcVar3;
  undefined4 uVar4;
  byte bVar5;
  int iVar6;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  int iStack_68;
  undefined4 uStack_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  int iStack_58;
  undefined1 auStack_50 [12];
  undefined4 uStack_44;
  undefined4 uStack_34;
  undefined4 uStack_24;
  undefined4 uStack_14;
  
  // Check if bit 0x200000 (0x15) is not set and param_2 differs from bit 0x2000000 (0x19)
  if ((((uint)this[0xaf] >> 0x15 & 1) == 0) &&
     (param_2 != ((byte)((uint)this[0xaf] >> 0x19) & 1))) {
    iVar1 = this[0xcd]; // +0x334: some stored value
    pcVar3 = *(code **)(*this + 0x104); // vtable offset 0x104: some method
    this[0xff] = (int)this; // +0x3fc: store self pointer
    *(undefined2 *)((int)this + 0x3fa) = 1; // +0x3fa: set some flag
    (*pcVar3)(&local_60); // Call vtable method
    uVar4 = local_60;
    iVar6 = FUN_00471610(); // Get some manager/global
    uVar2 = *(undefined4 *)(iVar6 + 0x34); // +0x34 from that manager
    uStack_44 = 0;
    uStack_34 = 0;
    uStack_24 = 0;
    uStack_14 = _DAT_00d5780c; // Global data
    FUN_00471610();
    FUN_00793640(); // Some initialization
    uStack_70 = uVar4;
    iStack_68 = iStack_58;
    uStack_64 = _DAT_00d5780c;
    uStack_6c = uVar2;
    FUN_0056b420(auStack_50,&uStack_70,&local_60); // Some transform/vector operation
    *(ulonglong *)(this + 0xf2) = CONCAT44(uStack_5c,local_60); // +0x3c8: store 64-bit value
    this[0xf4] = iStack_58; // +0x3d0: store
    this[0xf5] = iVar1; // +0x3d4: store
    *(ushort *)(this + 0xfe) = *(ushort *)(this + 0xfe) | 8; // +0x3f8: set bit 3
    this[0xaf] = this[0xaf] | 0x200000; // +0x2bc: set bit 0x200000
  }
  bVar5 = (byte)((uint)this[0xaf] >> 0x19) & 1; // Extract bit 0x2000000
  if ((bVar5 == 0) && (param_2 != 0)) {
    FUN_009a25b0(); // Some enable function
    this[0xaf] = this[0xaf] | 0x2000000; // +0x2bc: set bit 0x2000000
    return;
  }
  if ((bVar5 != 0) && (param_2 == 0)) {
    FUN_009a2fe0(); // Some disable function
    this[0xaf] = this[0xaf] & 0xfdffffff; // +0x2bc: clear bit 0x2000000
  }
  return;
}
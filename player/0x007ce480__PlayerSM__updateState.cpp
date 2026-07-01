// FUNC_NAME: PlayerSM::updateState
void __fastcall PlayerSM::updateState(int *this)
{
  code *pcVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined1 uStack_4;
  
  cVar3 = FUN_007cbc10(1);
  if (cVar3 == '\0') {
    this[0x74] = this[0x74] & 0xffffffbf; // +0x1D0 flags, clear bit 6
  }
  else {
    this[0x74] = this[0x74] | 0x40; // +0x1D0 flags, set bit 6
  }
  if (this[0x6d] == 0) { // +0x1B4 player index
    return;
  }
  if (this[0x6d] == 0x48) { // +0x1B4 player index
    return;
  }
  if (((uint)this[0x74] >> 6 & 1) == 0) { // +0x1D0 flags, bit 6
    pcVar1 = *(code **)(*this + 0x2c); // vtable offset 0x2c
    this[0x73] = 0x46f5c7b4; // +0x1CC some ID
    (*pcVar1)(0x46f5c7b4,1,1,0,0x3f800000,0x3f800000);
  }
  iVar2 = this[0x16]; // +0x58 some pointer
  if (this[0x6d] == 0) { // +0x1B4 player index
    iVar6 = 0;
  }
  else {
    iVar6 = this[0x6d] + -0x48; // +0x1B4 player index - 0x48
    if (iVar6 != 0) {
      iVar4 = FUN_0043b870(DAT_0112afb8);
      goto LAB_007ce51c;
    }
  }
  iVar4 = 0;
LAB_007ce51c:
  if (this[0x6f] != 0) { // +0x1BC some pointer
    if ((*(uint *)(iVar6 + 0x1f54) >> 0x11 & 1) != 0) { // +0x1F54 flags
      uStack_c = DAT_0112ba74;
      uStack_8 = 0;
      uStack_4 = 0;
      FUN_00408a00(&uStack_c,0);
    }
    if ((iVar4 != 0) && (cVar3 = FUN_0078a7d0(), cVar3 != '\0')) {
      FUN_007cc1f0(iVar6);
      FUN_0071ed70(1);
    }
    if (this[0x6d] == 0) { // +0x1B4 player index
      iVar5 = 0;
    }
    else {
      iVar5 = this[0x6d] + -0x48; // +0x1B4 player index - 0x48
    }
    if ((*(char *)(iVar5 + 0x1b8c) != '\0') && (((uint)this[0x74] >> 7 & 1) == 0)) { // +0x1B8C some flag, +0x1D0 bit 7
      FUN_007f63e0(0x32);
      if (this[0x6d] == 0) { // +0x1B4 player index
        iVar5 = 0;
      }
      else {
        iVar5 = this[0x6d] + -0x48; // +0x1B4 player index - 0x48
      }
      FUN_00716c50(iVar5);
    }
    this[0x70] = *(int *)(this[0x6f] + 0xc); // +0x1BC pointer, +0x1C0 = *(ptr+0xC)
    cVar3 = FUN_00898330(iVar6,5);
    if ((cVar3 == '\0') &&
       (((iVar4 == 0 || (*(float *)(iVar4 + 0x40) - *(float *)(iVar4 + 0x4c) <= DAT_00e44598)) &&
        ((*(uint *)(iVar6 + 0x1f98) & 0x50c) != 0)))) { // +0x1F98 flags
      this[0x74] = this[0x74] | 0x800; // +0x1D0 flags, set bit 11
    }
    FUN_007fff40(iVar6 + 0x1fe0); // +0x1FE0 some data
    FUN_007cc090(0);
  }
  FUN_00800670();
  FUN_007f62b0();
  FUN_007f63b0(1);
  if (this[0x6d] == 0) { // +0x1B4 player index
    iVar4 = 0;
  }
  else {
    iVar4 = this[0x6d] + -0x48; // +0x1B4 player index - 0x48
  }
  *(uint *)(iVar4 + 0x970) = *(uint *)(iVar4 + 0x970) | 0x10; // +0x970 flags
  if (this[0x6d] == 0) { // +0x1B4 player index
    iVar4 = 0;
  }
  else {
    iVar4 = this[0x6d] + -0x48; // +0x1B4 player index - 0x48
  }
  *(undefined1 *)(iVar4 + 0xa20) = 1; // +0xA20 some flag
  FUN_00800670();
  if (((uint)this[0x74] >> 8 & 1) == 0) { // +0x1D0 flags, bit 8
    this[0x74] = this[0x74] | 0x100; // +0x1D0 flags, set bit 8
    if (iVar2 != 0) {
      FUN_0043b870(DAT_01131018);
    }
    FUN_009ae900(1);
  }
  if ((*(uint *)(iVar6 + 0x1f54) >> 6 & 1) != 0) { // +0x1F54 flags, bit 6
    if (((uint)this[0x74] >> 0xf & 1) == 0) { // +0x1D0 flags, bit 15
      this[0x74] = this[0x74] | 0x8000; // +0x1D0 flags, set bit 15
      FUN_0043b870(DAT_01131018);
      FUN_009ae900(1);
    }
    if ((*(uint *)(iVar6 + 0x820) >> 2 & 1) == 0) { // +0x820 flags, bit 2
      this[0x74] = this[0x74] | 0x10000; // +0x1D0 flags, set bit 16
      *(uint *)(iVar6 + 0x820) = *(uint *)(iVar6 + 0x820) | 4; // +0x820 flags, set bit 2
    }
  }
  FUN_007ab9a0(0,1);
  FUN_007f62b0();
  FUN_007f6db0(0);
  FUN_00799570();
  FUN_007f63b0(1);
  *(uint *)(iVar2 + 0x970) = *(uint *)(iVar2 + 0x970) | 0x10; // +0x970 flags
  *(undefined1 *)(iVar2 + 0xa20) = 1; // +0xA20 some flag
  FUN_007cdaa0();
  if (*(char *)(DAT_01129904 + 0x3d) == '\0') { // global +0x3D
    this[0x74] = this[0x74] & 0xffbfffff; // +0x1D0 flags, clear bit 22
  }
  else {
    this[0x74] = this[0x74] | 0x400000; // +0x1D0 flags, set bit 22
    FUN_008c6de0();
  }
  FUN_006913c0(0xb);
  *(undefined1 *)((int)this + 0x20d) = 1; // +0x20D some flag
  return;
}
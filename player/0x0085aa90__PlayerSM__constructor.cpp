// FUNC_NAME: PlayerSM::constructor
undefined4 * __thiscall PlayerSM::constructor(undefined4 *this, undefined4 param_2)
{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 uVar3;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  FUN_009af100(param_2);
  uVar3 = DAT_00d61ae8;
  this[0x30] = 0; // +0xC0 - some state flag
  puVar1 = this + 0x2f; // +0xBC - vtable pointer
  *puVar1 = &PTR_LAB_00d58278;
  this[0x32] = uVar3; // +0xC8
  uVar3 = DAT_00d75478;
  *this = &PTR_FUN_00d754b0; // vtable
  *puVar1 = &PTR_FUN_00d75498; // secondary vtable
  this[0x33] = 0; // +0xCC
  this[0x34] = 0; // +0xD0
  this[0x35] = uVar3; // +0xD4
  this[0x36] = _DAT_00d5780c; // +0xD8
  this[0x37] = DAT_00d5ef90; // +0xDC
  this[0x38] = DAT_00d5efa4; // +0xE0
  this[0x39] = DAT_00d75474; // +0xE4
  this[0x3a] = DAT_00e44658; // +0xE8
  this[0x3b] = DAT_00e4475c; // +0xEC
  this[0x3c] = DAT_00d75470; // +0xF0
  this[0x3d] = DAT_00d60d04; // +0xF4
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  piVar2 = (int *)FUN_009c89c0();
  this[0x3f] = 0; // +0xFC
  this[0x40] = 0; // +0x100
  uVar3 = FUN_004265d0(&local_c,piVar2);
  this[0x41] = uVar3; // +0x104
  this[0x42] = piVar2; // +0x108
  (**(code **)(*piVar2 + 8))();
  uVar3 = DAT_00d5efa4;
  this[0x43] = 0; // +0x10C
  this[0x46] = uVar3; // +0x118
  this[0x47] = DAT_00d5e288; // +0x11C
  uVar3 = DAT_00e448cc;
  this[0x44] = 0; // +0x110
  this[0x45] = 0; // +0x114
  this[0x48] = uVar3; // +0x120
  this[0x49] = 0; // +0x124
  *(undefined2 *)(this + 0x5a) = 0; // +0x168
  this[0x5b] = 0; // +0x16C
  this[0x5c] = 0; // +0x170
  this[0x5d] = 0; // +0x174
  *(undefined2 *)(this + 0x5e) = 0; // +0x178
  this[0x5f] = 0; // +0x17C
  this[0x60] = 0; // +0x180
  this[0x61] = 0; // +0x184
  *(undefined2 *)(this + 0x62) = 0; // +0x188
  this[99] = 0; // +0x18C
  this[100] = 0; // +0x190
  this[0x65] = 0; // +0x194
  this[0x66] = 0; // +0x198
  this[0x67] = 0; // +0x19C
  this[0x68] = 0; // +0x1A0
  this[0x69] = 0; // +0x1A4
  this[0x6a] = 0; // +0x1A8
  this[0x6b] = 0; // +0x1AC
  this[0x6c] = 0; // +0x1B0
  this[0x6d] = 0; // +0x1B4
  this[0x70] = 0; // +0x1C0
  FUN_00858e80();
  this[0x3e] = this[3]; // +0xF8 = +0x0C
  FUN_009aefd0(puVar1,0x8000);
  return this;
}
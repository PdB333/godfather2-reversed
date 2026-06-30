// FUNC_NAME: SomeClass::dispatchAction
void __thiscall SomeClass::dispatchAction(int this, undefined4 param_2)
{
  int iVar1;
  float local_10;
  float local_c;
  
  if (*(char *)(this + 0x98) != '\0') {
    iVar1 = *(int *)(this + 0x24);
    switch(*(undefined1 *)(iVar1 + 0x10)) {
    case 0:
      // Action type 0: some initialization/reset
      FUN_004eec40();
      return;
    case 1:
      // Action type 1: process with parameter from offset +0x4c
      FUN_0040aee0(*(undefined4 *)(iVar1 + 0x4c));
      return;
    case 2:
      // Action type 2: complex operation with multiple parameters
      FUN_005149c0(param_2,this + 0x30,this + 0x40,this + 0x60,
                   *(undefined4 *)(this + 0x3c),*(undefined4 *)(this + 0x4c));
      return;
    case 4:
      // Action type 4: another complex operation
      FUN_005172c0(param_2,*(undefined4 *)(this + 0x88),*(undefined4 *)(iVar1 + 0x40),
                   *(undefined4 *)(this + 0x84),*(undefined4 *)(this + 0x8c),this + 0x70,
                   *(undefined4 *)(iVar1 + 0x44),*(undefined4 *)(iVar1 + 0x48),
                   *(undefined4 *)(iVar1 + 0x14));
      return;
    case 5:
      // Action type 5: some state change
      FUN_004ef1d0(1);
      return;
    case 6:
      // Action type 6: process data at offset +0x30
      FUN_004e69c0(this + 0x30);
      return;
    case 7:
      // Action type 7: conditional operation
      if (*(int *)(this + 0x28) != 0) {
        FUN_004e6b30();
        return;
      }
      break;
    case 8:
      // Action type 8: operation with two parameters
      FUN_004e44c0(*(undefined4 *)(this + 0x58),*(undefined4 *)(this + 0x54));
      return;
    case 10:
      // Action type 10: another two-parameter operation
      FUN_004e4400(*(undefined4 *)(this + 0x54),*(undefined4 *)(this + 0x58));
      return;
    case 0xb:
      // Action type 11: scaling operation with default values
      local_c = *(float *)(iVar1 + 0x40);
      if (local_c == 0.0) {
        local_c = DAT_00e2b04c;
      }
      local_10 = *(float *)(iVar1 + 0x44);
      if (local_10 == 0.0) {
        local_10 = DAT_00e2b04c;
      }
      FUN_0052e450(this + 0x80,*(undefined4 *)(this + 0x28),local_c,local_10);
      return;
    case 0xd:
      // Action type 13: some operation
      FUN_004e4550();
      return;
    case 0xe:
      // Action type 14: operation with two parameters
      FUN_004e4690(*(undefined4 *)(this + 0x84),*(undefined4 *)(this + 0x8c));
      return;
    case 0xf:
      // Action type 15: operation with three parameters
      FUN_004e4860(this + 0x30,*(undefined4 *)(this + 0x84),*(undefined4 *)(this + 0x8c));
      return;
    case 0x10:
      // Action type 16: some operation
      FUN_004e4930();
    }
  }
  return;
}
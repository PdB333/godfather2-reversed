// FUNC_NAME: CrashDumpManager::initialize
undefined4 * __thiscall CrashDumpManager::initialize(undefined4 *this, undefined4 param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  *this = &DAT_00d734fc; // +0x00 vtable placeholder
  DAT_0112a53c = this;
  this[1] = &DAT_00e30fe0; // +0x04 vtable placeholder
  FUN_0046c590(param_2);
  uVar2 = DAT_00d5d740;
  this[0x16] = &DAT_00e32854; // +0x58 error report callback
  this[0x1c] = uVar2; // +0x70
  this[0x1d] = uVar2; // +0x74
  uVar2 = _DAT_00d5780c;
  this[2] = &DAT_00d7352c; // +0x08 crash log buffer
  this[0x1e] = uVar2; // +0x78
  *this = &DAT_00d73558; // +0x00 final vtable
  this[1] = &DAT_00d73548; // +0x04 final vtable
  this[0x11] = &DAT_00d7351c; // +0x44 function table
  this[0x14] = &DAT_00d73518; // +0x50 function table
  this[0x16] = &DAT_00d73514; // +0x58 function table
  *(undefined1 *)(this + 0x22) = 0; // +0x88 flags
  *(undefined1 *)((int)this + 0x89) = 0;
  puVar1 = this + 0x11; // +0x44
  *(undefined8 *)(this + 0x28) = 0; // +0xA0
  *(undefined8 *)(this + 0x2a) = 0; // +0xA8
  this[0x2c] = 0; // +0xB0
  this[0x17] = 0x79e; // +0x5C stack frame size
  this[0x18] = 0; // +0x60
  this[0x19] = 0; // +0x64
  this[0x1a] = 0; // +0x68
  this[0x1b] = 0; // +0x6C
  this[0x1f] = 0; // +0x7C
  this[0x20] = 0; // +0x80
  this[0x23] = 0x79e; // +0x8C
  this[0x24] = 0; // +0x90
  this[0x25] = 0; // +0x94
  this[0x26] = 0; // +0x98
  this[0x27] = 0; // +0x9C
  if (DAT_0112db7c != 0) {
    FUN_00408900(puVar1,&DAT_0112db7c,0x8000);
  }
  if (DAT_012069c4 != 0) {
    FUN_00408900(puVar1,&DAT_012069c4,0x8000);
  }
  if (DAT_0112db74 != 0) {
    FUN_00408900(puVar1,&DAT_0112db74,0x8000);
  }
  return this;
}
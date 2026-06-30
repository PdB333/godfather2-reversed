// FUNC_NAME: InputManager::constructor
undefined4 * __fastcall InputManager::constructor(undefined4 *this)

{
  int iVar1;
  
  this[2] = 0;          // +0x08: some flag/state
  this[1] = 1;          // +0x04: initialized flag
  this[3] = &PTR_LAB_00d5c4d0; // +0x0C: vtable or function pointer table
  DAT_01129814 = this;  // global singleton pointer
  *this = &PTR_FUN_00d5c4d8; // +0x00: vtable pointer
  this[3] = &PTR_LAB_00d5c4d4; // +0x0C: another vtable/function table
  this[4] = 0;          // +0x10: some pointer/state
  *(undefined1 *)(this + 5) = 0x12; // +0x14: byte field (18 = 0x12)
  *(undefined1 *)((int)this + 0x15) = 1; // +0x15: byte field
  this[6] = 0;          // +0x18
  this[7] = 0;          // +0x1C
  this[8] = 0;          // +0x20
  this[9] = 0;          // +0x24
  this[10] = 0;         // +0x28
  this[0xb] = 0;        // +0x2C: bitfield for controller slots
  iVar1 = DAT_012233b4;  // some global state
  FUN_0040fc70(&LAB_0068c920); // register callback/handler
  this[0xb] = this[0xb] | 1 << (*(byte *)(iVar1 + 0x53d) & 0x1f); // set bit for specific controller
  this[0xc] = DAT_01205210; // +0x30: store some global pointer
  FUN_00408240(&DAT_01129aa0,"iMsgStartWaitingForControllerAttach"); // register message string
  FUN_00408240(&DAT_01129a98,"iMsgStopWaitingForControllerAttach"); // register message string
  if (DAT_012069c4 != 0) {
    FUN_00408900(this,&DAT_012069c4,0x8000); // register event handler with 0x8000 flag
  }
  if (DAT_012069b4 != 0) {
    FUN_00408900(this,&DAT_012069b4,0x8000); // register event handler with 0x8000 flag
  }
  return this;
}
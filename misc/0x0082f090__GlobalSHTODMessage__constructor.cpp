// FUNC_NAME: GlobalSHTODMessage::constructor
undefined4 * __fastcall GlobalSHTODMessage::constructor(undefined4 *this)
{
  undefined4 uVar1;
  undefined1 *puVar2;
  int local_10 [3];
  code *local_4;
  
  this[1] = 0;
  this[2] = 0;
  this[3] = 0;
  this[4] = 0;
  this[5] = 0;
  this[6] = 0;
  this[7] = 0;
  *(undefined1 *)(this + 8) = 1; // +0x20: some boolean flag
  *this = &PTR_FUN_00d737fc; // vtable pointer
  this[9] = 1; // +0x24: some count or flag
  FUN_00822f30(); // likely base class constructor or initialization
  this[0x50] = &PTR_FUN_00d737f8; // +0x140: another vtable pointer
  this[0x51] = 0; // +0x144: null pointer
  uVar1 = FUN_009c8e80(0x40); // allocate 0x40 bytes
  this[0x52] = uVar1; // +0x148: pointer to allocated memory
  this[0x53] = 0; // +0x14c: null
  this[0x54] = 0x10; // +0x150: size or count = 16
  local_10[0] = 0;
  local_10[1] = 0;
  local_10[2] = 0;
  local_4 = (code *)0x0;
  FUN_004d4ad0(local_10, &DAT_00e2f0b0, "GlobalSHTODMessage", "Sequence"); // create a named sequence object
  FUN_004d3e20(local_10); // probably get or resolve the sequence
  puVar2 = (undefined1 *)this[4]; // +0x10: some pointer
  if (puVar2 == (undefined1 *)0x0) {
    puVar2 = &DAT_0120546e; // default string or data
  }
  uVar1 = FUN_004dafd0(puVar2); // hash or register string
  this[3] = uVar1; // +0x0c: store result
  if (local_10[0] != 0) {
    (*local_4)(local_10[0]); // cleanup callback
  }
  return this;
}
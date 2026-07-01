// FUNC_NAME: SomeClass::constructor
undefined4 * __fastcall SomeClass::constructor(undefined4 *this)
{
  undefined4 uVar1;
  
  this[1] = &PTR_LAB_00d7bc50; // vtable or base class pointer
  DAT_01129908 = this; // global singleton assignment
  *this = &PTR_FUN_00d7bc58; // vtable pointer
  this[1] = &PTR_LAB_00d7bc54; // secondary vtable or interface pointer
  uVar1 = FUN_009c8e80(0x160); // allocate 0x160 bytes (352 bytes)
  this[2] = uVar1; // +0x08: pointer to allocated memory
  this[3] = 0; // +0x0C: some counter or state
  this[4] = 8; // +0x10: initial capacity or size (8)
  this[5] = 0; // +0x14: another counter or index
  *(undefined1 *)(this + 6) = 0; // +0x18: byte flag
  *(undefined1 *)((int)this + 0x19) = 0; // +0x19: another byte flag
  FUN_00463980(0x253131b5,this,0x53); // register with debug/logging system (hash, this, size)
  return this;
}
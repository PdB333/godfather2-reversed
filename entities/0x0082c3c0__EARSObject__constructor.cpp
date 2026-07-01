// FUNC_NAME: EARSObject::constructor
undefined4 * __fastcall EARSObject::constructor(undefined4 *this)

{
  undefined4 uVar1;
  
  *this = &PTR_FUN_00d737f8; // vtable pointer
  this[1] = 0;               // +0x04: some flag or counter
  uVar1 = FUN_009c8e80(0x40); // allocate 0x40 bytes (64 bytes) for internal data
  this[2] = uVar1;           // +0x08: pointer to allocated data
  this[3] = 0;               // +0x0C: some pointer or flag
  this[4] = 0x10;            // +0x10: size or count (16)
  return this;
}
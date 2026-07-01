// FUNC_NAME: Object::constructor
void __fastcall Object::constructor(undefined4 *this)
{
  // Set primary vtable pointer (offset +0x00)
  *this = &PTR_FUN_00d58a74;

  // Set secondary vtable pointer at offset +0x3C (0xF * 4)
  this[0xF] = &PTR_LAB_00d58a64;

  // Set another vtable pointer at offset +0x48 (0x12 * 4)
  this[0x12] = &PTR_LAB_00d58a60;

  // Call base class constructor
  FUN_0046c640();
  return;
}
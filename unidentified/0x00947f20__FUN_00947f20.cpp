// FUNC_NAME: SomeClass::constructor
undefined4 * __fastcall SomeClass::constructor(undefined4 *this)
{
  FUN_004b1da0(1,1);
  *this = &PTR_LAB_00d8b538; // vtable pointer
  this[6] = &PTR_LAB_00d8b4a0; // +0x18: another vtable or interface pointer
  this[7] = &LAB_00947e10; // +0x1C: function pointer (likely a callback or method)
  FUN_004a8f30(0);
  this[5] = this + 6; // +0x14: pointer to +0x18 (self-referential pointer)
  return this;
}
// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d68494;
  
  // Call destructors for member objects at offsets +0x8 and +0xC
  FUN_009c8eb0(this[2]); // +0x8: member object destructor
  FUN_009c8eb0(this[3]); // +0xC: member object destructor
  
  return;
}
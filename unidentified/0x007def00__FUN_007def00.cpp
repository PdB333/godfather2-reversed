// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  int *piVar1;
  
  *this = &PTR_LAB_00d6f784; // vtable pointer
  piVar1 = (int *)FUN_007ab150(); // likely some manager or system
  (**(code **)(*piVar1 + 4))(this[0x1d]); // call a function on a member at offset 0x74 (0x1d * 4)
  *(uint *)(this[0x16] + 0x249c) = *(uint *)(this[0x16] + 0x249c) & 0x7fffffff; // clear high bit of some flag
  FUN_0045f2a0(0); // release or cleanup
  *this = &PTR_LAB_00d6b95c; // another vtable pointer (base class)
  FUN_0080ea60(); // base destructor
  return;
}
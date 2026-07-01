// FUNC_NAME: UnknownClass::Destructor (likely a gameplay manager destructor)

void __fastcall UnknownClassDestructor(uint *this)
{
  int *piVar1;

  *this = &PTR_LAB_00d6e510; // vtable assignment
  piVar1 = (int *)FUN_007ab150(); // probably get some subsystem
  (**(code **)(*piVar1 + 4))(1); // release reference (ref count decrement)
  piVar1 = (int *)FUN_007ab130(); // another subsystem get
  (**(code **)(*piVar1 + 4))(this[0x1d]); // release reference with argument
  *(this[0x16] + 0x249c) &= 0xbfffffff; // clear bit 30 of some flag at +0x249c
  if (this[0x1f] != 0) {
    FUN_004daf90(this + 0x1f); // likely free/delete object at +0x7c
  }
  *this = &PTR_LAB_00d6b95c; // secondary vtable assignment
  FUN_0080ea60(); // likely cleanup function
  return;
}
// FUNC_NAME: UnknownClass::destructor
undefined4 * __thiscall FUN_006e0750(undefined4 *this, byte flags)
{
  int *piVar1;
  
  *this = &PTR_FUN_00d5f784;
  this[2] = &PTR_LAB_00d5f77c;
  if (this[0x7b] != 0) {
    FUN_004daf90(this + 0x7b);  // likely operator delete on a sub-object at offset 0x1EC
  }
  if (this[0x49] != 0) {
    FUN_004daf90(this + 0x49);  // likely operator delete on a sub-object at offset 0x124
  }
  FUN_006c9820();  // unknown cleanup function
  if ((flags & 1) != 0) {
    piVar1 = (int *)FUN_009c8f80();  // likely operator new or memory allocator
    (**(code **)(*piVar1 + 4))(this, 0x200);  // call vtable function to free memory (size 0x200)
  }
  return this;
}
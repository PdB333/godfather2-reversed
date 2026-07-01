// FUNC_NAME: SomeManager::constructor
undefined4 * __thiscall SomeManager::constructor(undefined4 *this, byte allocFlag)
{
  *this = &PTR_FUN_00d79b04;  // set vtable pointer
  this[0xf] = &PTR_LAB_00d79af4;  // set interface vtable pointer at offset 0x3C
  this[0x12] = &PTR_LAB_00d79af0; // set another interface vtable pointer at offset 0x48
  FUN_008a1380();                 // call base constructor (e.g., Framework::Object)
  if ((allocFlag & 1) != 0) {
    FUN_0043b960(this, 100);      // custom deallocation based on flag (size 100? or object size?)
  }
  return this;
}
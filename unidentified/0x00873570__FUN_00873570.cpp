// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param2, undefined4 param3)
{
  int *listHead;
  int currentListHead;
  int newListHead;
  int unaff_retaddr;
  
  FUN_0086b060(param2, param3);
  *this = &PTR_LAB_00d76278; // vtable setup
  listHead = this + 0x18; // +0x60: list head pointer
  *listHead = 0;
  this[0x19] = 0; // +0x64: list tail pointer
  param3 = 0;
  (**(code **)(**(int **)(this[0x15] + 4) + 0x10))(0x10e5319e, &param3); // some virtual call
  currentListHead = *listHead;
  if (unaff_retaddr == 0) {
    if (currentListHead != 0) {
      FUN_004daf90(listHead); // likely list destructor or cleanup
      *listHead = 0;
    }
    return this;
  }
  newListHead = unaff_retaddr + 0x48;
  if (currentListHead != newListHead) {
    if (currentListHead != 0) {
      FUN_004daf90(listHead);
    }
    *listHead = newListHead;
    if (newListHead != 0) {
      this[0x19] = *(undefined4 *)(unaff_retaddr + 0x4c);
      *(int **)(unaff_retaddr + 0x4c) = listHead;
      return this;
    }
  }
  return this;
}
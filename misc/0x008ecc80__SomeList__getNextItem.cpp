// FUNC_NAME: SomeList::getNextItem
int __fastcall SomeList::getNextItem(int this)
{
  int iVar1;
  int local_8;
  int local_4;
  
  FUN_008ec930(&local_8, &stack0x00000004);
  iVar1 = *(int *)(this + 0x30); // +0x30: some current/next pointer
  if ((local_8 == 0) || (local_8 != this + 0x2c)) { // +0x2c: list head sentinel?
    FUN_00b97aea(); // assertion failure
  }
  if (local_4 != iVar1) {
    if (local_8 == 0) {
      FUN_00b97aea(); // assertion failure
    }
    if (local_4 == *(int *)(local_8 + 4)) {
      FUN_00b97aea(); // assertion failure
    }
    return local_4 + 0x10; // +0x10: offset to item data
  }
  return 0; // no more items
}
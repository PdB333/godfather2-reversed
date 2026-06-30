// FUNC_NAME: SomeClass::getTotalSize
int __fastcall SomeClass::getTotalSize(int this)
{
  int iVar1;
  int totalSize;
  uint index;
  
  index = 0;
  totalSize = 0x14; // base size +0x14
  if (*(int *)(this + 0x20) != 0) { // +0x20: count of items
    do {
      iVar1 = FUN_006b2320(); // likely getItemSize(index)
      index = index + 1;
      totalSize = totalSize + iVar1;
    } while (index < *(uint *)(this + 0x20));
  }
  return totalSize;
}
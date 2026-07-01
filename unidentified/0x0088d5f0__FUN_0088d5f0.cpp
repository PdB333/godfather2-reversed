// FUNC_NAME: SomeClass::findFirstMatchingChild
int __thiscall SomeClass::findFirstMatchingChild(int this, undefined4 param_2)
{
  int iVar1;
  byte bVar2;
  
  bVar2 = 0;
  if (*(int *)(this + 0x148) != 0) { // +0x148: childCount
    do {
      iVar1 = FUN_00889f70(param_2); // likely a predicate check on child
      if (iVar1 != 0) {
        return iVar1;
      }
      bVar2 = bVar2 + 1;
    } while ((uint)bVar2 < *(uint *)(this + 0x148)); // iterate through children
  }
  return 0;
}
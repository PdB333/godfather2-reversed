// FUNC_NAME: SomeClass::isValidSlotOrSomething
undefined4 __thiscall FUN_0078db50(int this, undefined4 param_2)
{
  int iVar1;
  char cVar2;
  uint uVar3;
  
  uVar3 = 0;
  // Check if count at +0x54 is zero
  if (*(int *)(this + 0x54) == 0) {
    return 0;
  }
  // Loop through entries at +0x50 (array of 8-byte elements)
  while (((iVar1 = *(int *)(*(int *)(this + 0x50) + uVar3 * 8), iVar1 == 0 || (iVar1 == 0x48)) ||
         (cVar2 = FUN_0078e8a0(param_2), cVar2 == '\0'))) {
    uVar3 = uVar3 + 1;
    // Check if we've exceeded the count
    if (*(uint *)(this + 0x54) <= uVar3) {
      return 0;
    }
  }
  return 1;
}
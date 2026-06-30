// FUNC_NAME: SomeClass::updateSomething
void __thiscall SomeClass::updateSomething(int *this)
{
  int iVar1;
  int iVar2;
  
  iVar1 = *this;
  if (((iVar1 != 0) && (iVar2 = this[2], iVar2 != 0)) &&
     (*(byte *)(iVar2 + 0x21) = *(byte *)(iVar2 + 0x21) | 4, (*(byte *)(iVar2 + 0x21) & 2) != 0)) {
    // Call to process something with the two objects
    // param1: iVar1 (first object), param2: iVar2 (second object), param3: 0, param4: 1, param5: 0
    FUN_006a8100(iVar1,iVar2,0,1,0);
  }
  return;
}
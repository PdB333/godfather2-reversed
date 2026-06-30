// FUNC_NAME: SomeClass::someMethod
void __thiscall SomeClass::someMethod(int *this, undefined4 param_2)
{
  int iVar1;
  int *piStack_4;
  
  piStack_4 = this;
  piStack_4 = (int *)(**(code **)(*this + 0x50))(); // Call virtual function at vtable+0x50
  FUN_0064b810(0x20,&piStack_4); // Some function call with size 0x20 and pointer
  iVar1 = (**(code **)(*this + 0x50))(); // Call same virtual function again
  param_2 = *(undefined4 *)(&DAT_00f0cdb0 + iVar1 * 4); // Lookup value from global table at 0xf0cdb0
  FUN_0064b810(0x20,&param_2); // Another call with size 0x20 and pointer
  return;
}
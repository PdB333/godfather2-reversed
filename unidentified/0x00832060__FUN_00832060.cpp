// FUNC_NAME: SomeClass::updateSomething
void __thiscall SomeClass::updateSomething(int this, undefined4 param2)
{
  int iVar1;
  undefined1 local_100 [80];
  undefined1 local_b0 [80];
  undefined1 local_60 [92];
  
  if (*(int *)(this + 0x24) == 0) {
    iVar1 = FUN_0082ff50(local_60, param2);
  }
  else if (*(int *)(this + 0x24) == 1) {
    iVar1 = FUN_0082fd00(local_100, param2, 0);
  }
  else {
    iVar1 = FUN_0082fd00(local_b0, param2, 0);
  }
  if (this + 0x30 != iVar1) {
    FUN_00820830(iVar1);
    *(undefined4 *)(this + 0x7c) = *(undefined4 *)(iVar1 + 0x4c);
  }
  return;
}
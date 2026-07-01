// FUNC_NAME: SomeClass::handleStateTransition
void __thiscall SomeClass::handleStateTransition(int this, undefined4 param_2)
{
  undefined4 uVar1;
  undefined1 local_190 [128];
  undefined1 local_110 [128];
  undefined1 local_90 [140];
  
  if (*(int *)(this + 0x24) == 0) {
    uVar1 = FUN_0082d930(local_90,param_2);
    FUN_0082d200(uVar1);
    return;
  }
  if (*(int *)(this + 0x24) != 1) {
    uVar1 = FUN_0082d6e0(local_110,param_2,0);
    FUN_0082d200(uVar1);
    return;
  }
  uVar1 = FUN_0082d6e0(local_190,param_2,0);
  FUN_0082d200(uVar1);
  return;
}
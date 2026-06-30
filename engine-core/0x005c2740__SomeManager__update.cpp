// FUNC_NAME: SomeManager::update
void SomeManager::update(int param_1)

{
  int iVar1;
  
  if (DAT_01205664 == 0) {
    iVar1 = FUN_005c4410(200,0);
    if (iVar1 == 0) {
      DAT_01205664 = 0;
    }
    else {
      DAT_01205664 = FUN_005c3070();
    }
    FUN_005c31d0();
  }
  iVar1 = FUN_005c3ef0(param_1);
  if ((iVar1 != 0) && ((int *)(iVar1 + -0x10) != (int *)0x0)) {
    (**(code **)(*(int *)(iVar1 + -0x10) + 0x2c))();
  }
  return;
}
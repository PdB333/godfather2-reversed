// FUNC_NAME: LinkedList::destroyAllAndReset
void LinkedList::destroyAllAndReset(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  for (puVar1 = (undefined4 *)*param_1; puVar1 != param_1; puVar1 = (undefined4 *)*puVar1) {
    if ((undefined4 *)puVar1[2] != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)puVar1[2])(1);
    }
  }
  FUN_0089ecc0();
  *param_1 = param_1;
  param_1[1] = param_1;
  return;
}
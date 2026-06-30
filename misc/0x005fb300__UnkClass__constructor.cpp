// FUNC_NAME: UnkClass::constructor
undefined4 * UnkClass::constructor(undefined4 *this)

{
  undefined4 *eax;
  undefined4 uVar1;
  undefined4 *result;
  int index;
  int *listNode;
  undefined4 stack_c;
  undefined4 stack_8;
  undefined4 stack_4;
  
  listNode = (int *)*eax;
  index = eax[1];
  (**(code **)(*listNode + 8))(listNode);
  if (index == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_004265d0(index,listNode);
  }
  FUN_005fba60(this,listNode,uVar1);
  result = (undefined4 *)this[1];
  if (result == (undefined4 *)0x0) {
    stack_c = 0;
    stack_8 = 0;
    stack_4 = 0;
    result = &stack_c;
  }
  index = (*(code *)**(undefined4 **)*this)(0xc,result);
  if (index != 0) {
    *(int *)index = index;
  }
  if ((int *)(index + 4) != (int *)0x0) {
    *(int *)(index + 4) = index;
  }
  this[7] = 0;
  this[6] = index;
  return this;
}
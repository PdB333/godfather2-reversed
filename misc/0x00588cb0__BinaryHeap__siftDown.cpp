// FUNC_NAME: BinaryHeap::siftDown
void BinaryHeap::siftDown(int param_1, int param_2, undefined4 param_3, undefined4 param_4)
{
  int iVar1;
  int iVar2;
  char cVar3;
  int in_EAX;
  int iVar4;
  
  iVar1 = in_EAX * 2;
  iVar2 = in_EAX;
  while (iVar4 = iVar1 + 2, iVar4 < param_2) {
    cVar3 = FUN_00587840(); // compare function (likely less-than)
    if (cVar3 != '\0') {
      iVar4 = iVar1 + 1;
    }
    *(undefined4 *)(param_1 + iVar2 * 4) = *(undefined4 *)(param_1 + iVar4 * 4);
    iVar2 = iVar4;
    iVar1 = iVar4 * 2;
  }
  if (iVar4 == param_2) {
    *(undefined4 *)(param_1 + iVar2 * 4) = *(undefined4 *)(param_1 + -4 + param_2 * 4);
  }
  FUN_00588e90(param_1,in_EAX,param_3,param_4); // bubble up the inserted element
  return;
}
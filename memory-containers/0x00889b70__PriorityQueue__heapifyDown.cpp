// FUNC_NAME: PriorityQueue::heapifyDown
void PriorityQueue::heapifyDown(undefined4 *param_1, uint *param_2, uint *param_3, undefined4 param_4)

{
  uint *puVar1;
  uint *puVar2;
  uint *puVar3;
  undefined4 uVar4;
  uint *puVar5;
  
  puVar3 = param_2;
  FUN_008894f0(param_1,param_2,param_4);
  uVar4 = param_4;
  puVar5 = puVar3;
  if (puVar3 < param_3) {
    do {
      puVar1 = (uint *)*param_1;
      puVar2 = (uint *)*puVar5;
      if (((float)puVar1[3] < (float)puVar2[3]) ||
         (((float)puVar1[3] <= (float)puVar2[3] && (puVar1 < puVar2)))) {
        *puVar5 = (uint)puVar1;
        param_2 = puVar2;
        FUN_008889c0(param_1,0,(int)puVar3 - (int)param_1 >> 2,0,&param_2,uVar4);
      }
      puVar5 = puVar5 + 1;
    } while (puVar5 < param_3);
  }
  FUN_00889540(param_1,puVar3,uVar4);
  return;
}
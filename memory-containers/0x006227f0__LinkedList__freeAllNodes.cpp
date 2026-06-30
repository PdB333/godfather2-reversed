// FUNC_NAME: LinkedList::freeAllNodes
void __thiscall LinkedList::freeAllNodes(int param_1, int *param_2)
{
  char cVar1;
  int *piVar2;
  
  cVar1 = *(char *)((int)param_2 + 0x15); // +0x15: node->isFree flag
  while (cVar1 == '\0') {
    FUN_006227f0(param_2[2]); // param_2[2] = node->pNext, recursive call
    piVar2 = (int *)*param_2; // *param_2 = node->pPrev
    (**(code **)(**(int **)(param_1 + 4) + 4))(param_2,0x18); // call allocator->free(node, 0x18)
    param_2 = piVar2;
    cVar1 = *(char *)((int)piVar2 + 0x15); // +0x15: check if previous node is free
  }
  return;
}
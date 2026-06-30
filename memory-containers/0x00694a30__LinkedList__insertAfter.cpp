// FUNC_NAME: LinkedList::insertAfter
void __thiscall LinkedList::insertAfter(int param_1, int param_2)
{
  int *piVar1;
  int *piVar2;
  
  piVar1 = *(int **)(param_2 + 8); // +0x8: next pointer
  *(int *)(param_2 + 8) = *piVar1; // set this->next = node->next
  if (*(char *)(*piVar1 + 0x29) == '\0') { // check if node is not a sentinel
    *(int *)(*piVar1 + 4) = param_2; // node->prev = this
  }
  piVar1[1] = *(int *)(param_2 + 4); // node->next->prev = this->prev
  if (param_2 == *(int *)(*(int *)(param_1 + 4) + 4)) { // if this is the head
    *(int **)(*(int *)(param_1 + 4) + 4) = piVar1; // head->prev = node
    *piVar1 = param_2; // node->next = this
    *(int **)(param_2 + 4) = piVar1; // this->prev = node
    return;
  }
  piVar2 = *(int **)(param_2 + 4); // this->prev
  if (param_2 == *piVar2) { // if this is the tail
    *piVar2 = (int)piVar1; // prev->next = node
    *piVar1 = param_2; // node->next = this
    *(int **)(param_2 + 4) = piVar1; // this->prev = node
    return;
  }
  piVar2[2] = (int)piVar1; // prev->next->prev = node
  *piVar1 = param_2; // node->next = this
  *(int **)(param_2 + 4) = piVar1; // this->prev = node
  return;
}
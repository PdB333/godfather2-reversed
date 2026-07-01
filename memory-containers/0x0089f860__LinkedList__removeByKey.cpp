// FUNC_NAME: LinkedList::removeByKey
void __thiscall LinkedList::removeByKey(undefined4 *param_1, int *param_2)

{
  undefined4 *puVar1;
  int *piVar2;
  
  puVar1 = (undefined4 *)*param_1;
  while (puVar1 != param_1) {
    piVar2 = puVar1 + 2;
    puVar1 = (undefined4 *)*puVar1;
    if (*piVar2 == *param_2) {
      // Found matching key, unlink node from doubly linked list
      piVar2 = (int *)puVar1[1];
      *(int *)piVar2[1] = *piVar2;          // next->prev = prev
      *(int *)(*piVar2 + 4) = piVar2[1];     // prev->next = next
      if (piVar2[2] != 0) {
        FUN_004daf90(piVar2 + 2);            // Deallocate node data if present
      }
      FUN_009c8f10(piVar2);                  // Remove node (likely delete or free)
    }
  }
  return;
}
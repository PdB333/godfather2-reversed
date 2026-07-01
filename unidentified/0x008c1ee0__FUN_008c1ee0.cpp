// FUNC_NAME: SomeClass::processPendingDeletes
void SomeClass::processPendingDeletes(int thisPtr)
{
  int current = *(int *)(thisPtr + 4); // +0x04: pointer to linked list head (pending delete list)
  undefined4 iterator = 0xffffffff;    // iterator for the linked list traversal
  
  while ((current != 0 && (current = FUN_008c00a0(&iterator), current != 0))) {
    FUN_006b68c0(current, 0, 0, 0);    // likely deleteEntity or releaseResource(current, 0, 0, 0)
    current = *(int *)(thisPtr + 4);    // re-fetch head in case list changed
  }
}
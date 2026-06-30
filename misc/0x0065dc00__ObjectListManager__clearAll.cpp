// FUNC_NAME: ObjectListManager::clearAll
void __thiscall ObjectListManager::clearAll(void)
{
  int iNextNode;
  int iCurrentNode;
  uint uiIdx;
  int *pThis;

  pThis = this; // this in ESI

  // Get head of linked list from internal data structure at this[0] -> offset +0x08
  iCurrentNode = **(int **)(*pThis + 8);
  while (iCurrentNode != 0) {
    // Save next node before deletion
    iNextNode = **(int **)(iCurrentNode + 8);
    // Free the data object pointed by this node
    FUN_009c8f10(*(int **)(iCurrentNode + 8));
    // Free the node itself
    FUN_009c8eb0(iCurrentNode);
    // Decrement active count (at this+0x10)
    pThis[4] = pThis[4] - 1;
    iCurrentNode = iNextNode;
  }

  // Zero out the pointer array at the internal data structure's offset +0x08
  uiIdx = 0;
  do {
    *(undefined4 *)(*(int *)(*pThis + 8) + uiIdx * 4) = 0;
    uiIdx = uiIdx + 1;
  } while (uiIdx <= (uint)pThis[2]); // capacity at this+0x08

  // Reset count (at this+0x04)
  pThis[1] = 0;
  return;
}
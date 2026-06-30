// FUNC_NAME: EARSList::replaceHead
void __thiscall EARSList::replaceHead(void *thisObj, void *newNodeContainer)
{
  EARSList *list; // this->0x2688 is a list head pointer
  int *headPtr;
  int mutexReady;
  void *rawNode;

  // Check global mutex readiness (likely EARS mutex system)
  mutexReady = FUN_007f41e0();
  if (mutexReady != 0) {
    // Acquire mutex (0x400000 is a mutex handle or lock type)
    FUN_004abc20(0x400000);

    // The list head pointer offset (each node's next pointer is at +4, and nodes are intrusive)
    headPtr = (int *)((char *)thisObj + 0x2688);

    // newNodeContainer is a struct containing an embedded list node at offset 0x48.
    // If not null, adjust to pointer to the embedded node.
    if (newNodeContainer == (void *)0x0) {
      rawNode = (void *)0x0;
    }
    else {
      rawNode = (void *)((char *)newNodeContainer + 0x48);
    }

    // Only update if the head is different
    if (*headPtr != (int)rawNode) {
      // Remove existing head node (if any) from the list
      if (*headPtr != 0) {
        FUN_004daf90(headPtr);
      }

      // Set new head
      *headPtr = (int)rawNode;

      // If new node is valid, set its "link" field (offset +4) to point back to the head pointer.
      // Additionally, save the old link value into the list's tail pointer (offset 0x268c).
      if (rawNode != (void *)0x0) {
        *(int *)((char *)thisObj + 0x268c) = *(int *)((char *)rawNode + 4);
        *(int **)((char *)rawNode + 4) = headPtr;
      }
    }
  }
  return;
}
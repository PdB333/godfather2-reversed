// FUNC_NAME: EntityDataManager::cleanupDynamicResources
void __thiscall EntityDataManager::cleanupDynamicResources(bool freeAltBuffer)
{
  // local_18 likely stores vtable pointer for SEH or scope guard
  void** local_18 = &PTR_FUN_00e31e2c;  // global vtable/data pointer
  
  // Offset +0x48: pointer to a linked list node (e.g., event handlers or children)
  int* listNode;
  if (this == (EntityDataManager*)0x0) {
    listNode = (int*)0x0;
  }
  else {
    listNode = (int*)((int)this + 0x48);
  }

  int savedNext = 0;
  if (listNode != (int*)0x0) {
    savedNext = listNode[1];                   // save original next pointer (offset +4)
    listNode[1] = (int)&listNode;              // temporarily rewire next to local variable
  }

  // Offset +0x114: primary data buffer (always freed)
  int primaryBuffer = *(int*)((int)this + 0x114);
  FUN_00408a00(&primaryBuffer, 0);             // deallocate or release primary buffer

  // Offset +0x11c or +0x124: secondary buffer based on flag
  int secondaryBuffer;
  if (freeAltBuffer == false) {
    secondaryBuffer = *(int*)((int)this + 0x11c);
  }
  else {
    secondaryBuffer = *(int*)((int)this + 0x124);
  }
  FUN_00408a00(&secondaryBuffer, 0);           // deallocate or release secondary buffer

  // If a list node was present, clean up the linked list structure
  if (listNode != (int*)0x0) {
    FUN_004daf90(&listNode);                   // remove node from list or free the list
  }

  return;
}
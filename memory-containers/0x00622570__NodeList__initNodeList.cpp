// FUNC_NAME: NodeList::initNodeList
void __thiscall NodeList::initNodeList(void *srcObj)
{
  int *vtable = *(int **)srcObj;
  int sizeOrFlag = *(int *)((char *)srcObj + 4);
  // Call virtual function at vtable index 2 (offset +8) on the source object
  (*(void (__thiscall **)(int *))(*vtable + 8))(vtable);
  int copyResult = 0;
  if (sizeOrFlag != 0) {
    // Likely allocates or copies data from source object
    copyResult = FUN_004265d0(sizeOrFlag, vtable);
  }
  // Initialize some internal state using source vtable and copy result
  FUN_006235f0(this, vtable, copyResult);
  // Allocate and initialize a sentinel node for a doubly linked list
  ListNode *node = (ListNode *)FUN_00623df0();
  this->listHead = node;
  // Set node fields: flag at +0x15 = 1, and self-circular pointers
  *(unsigned char *)((char *)node + 0x15) = 1;
  node->prev = node;               // node+4 = node
  node->self = node;               // node+0 = node
  node->next = node;               // node+8 = node
  this->field_20 = 0;
}
// FUNC_NAME: LinkedList::~LinkedList
undefined4 * __thiscall LinkedList::~LinkedList(undefined4 *this, byte destroyFlag)
{
  undefined4 *nextNode;
  undefined4 *currentNode;
  
  // Set vtable pointer (class identifier)
  *this = &PTR_LAB_00e42de4;
  
  // Traverse linked list starting from offset +4 (head pointer)
  currentNode = (undefined4 *)this[1]; // +0x4: head of list
  while (currentNode != (undefined4 *)0x0) {
    nextNode = (undefined4 *)currentNode[2]; // +0x8: next pointer
    // Clear node fields (first three words)
    *currentNode = 0;          // +0x0: data or prev
    currentNode[1] = 0;        // +0x4: data or next? (actually cleared)
    currentNode[2] = 0;        // +0x8: next pointer
    currentNode = nextNode;
  }
  
  // If destroy flag is set, call memory deallocation function
  if ((destroyFlag & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}
// FUNC_NAME: TLinkedList::~TLinkedList
undefined4 * __thiscall TLinkedList::~TLinkedList(undefined4 *this, byte deleteFlag)
{
  undefined4 *nextNode;
  undefined4 *currentNode;
  
  // Set vtable pointer for proper destruction chain
  *this = (undefined4 *)&vtable_TLinkedList; // +0x00: vtable
  // Head pointer at +0x04
  currentNode = (undefined4 *)this[1];
  while (currentNode != (undefined4 *)0x0) {
    nextNode = (undefined4 *)currentNode[1]; // +0x04: next node
    currentNode[1] = 0; // Clear next pointer
    *currentNode = 0;   // Clear data field (assumed pointer or value)
    currentNode = nextNode;
  }
  if ((deleteFlag & 1) != 0) {
    // Custom deallocation for the object itself
    FUN_009c8eb0(this); // Likely operator delete or heap free
  }
  return this;
}
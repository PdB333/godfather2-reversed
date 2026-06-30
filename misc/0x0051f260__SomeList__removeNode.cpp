// FUNC_NAME: SomeList::removeNode
void __fastcall SomeList::removeNode(undefined4 *this)
{
  int *nodePtr;
  int nodeIndex;
  int *prevNode;
  int *nextNode;
  
  nodePtr = (int *)(this + 0x49);  // +0x124 offset to list node pointer
  nodeIndex = *nodePtr;
  if (nodeIndex != 0) {
    prevNode = *(int **)(nodeIndex + 4);  // +0x4 offset to previous node pointer
    if (prevNode == nodePtr) {
      // Node is the head of the list
      *(undefined4 *)(nodeIndex + 4) = this[0x4a];  // +0x128 offset to next node pointer
      *this = &PTR_LAB_00e38340;  // Set vtable to base class
      return;
    }
    nextNode = (int *)prevNode[1];  // +0x4 offset to next node pointer
    while (nextNode != nodePtr) {
      prevNode = (int *)prevNode[1];  // +0x4 offset to next node pointer
      nextNode = (int *)prevNode[1];  // +0x4 offset to next node pointer
    }
    prevNode[1] = this[0x4a];  // +0x128 offset to next node pointer
  }
  *this = &PTR_LAB_00e38340;  // Set vtable to base class
  return;
}
// FUNC_NAME: DoublyLinkedListBase::removeNode
void DoublyLinkedListBase::removeNode(void)
{
  char cVar1;
  int *nodePtr;
  
  // unaff_ESI is assumed to be 'this' in __thiscall
  // nodePtr[0x24] = prev node pointer (offset 0x90)
  // nodePtr[0x25] = next node pointer (offset 0x94)
  
  // If we have a previous node, update its next pointer to skip this node
  if (this[0x24] != 0) {
    *(int *)(this[0x24] + 0x94) = this[0x25]; // prev->next = this->next
  }
  
  // If we have a next node, update its prev pointer to skip this node
  if (this[0x25] != 0) {
    *(int *)(this[0x25] + 0x90) = this[0x24]; // next->prev = this->prev
  }
  
  // If the list head pointer points to this node, call the head update function
  if ((int *)*this != (int *)0x0) {
    (**(code **)(*(int *)*this + 4))(); // likely virtual function to update head/tail
  }
  
  // Clear this node's stored head pointer
  *this = 0;
  
  // Attempt to free/cleanup this node
  cVar1 = FUN_005c43d0(this); // likely memory deallocation or destructor
  if (cVar1 == '\0') {
    // If deallocation fails, call some global allocator function
    (**(code **)(**(int **)(DAT_012234ec + 4) + 4))(); // likely Allocator::free or similar
  }
  return;
}
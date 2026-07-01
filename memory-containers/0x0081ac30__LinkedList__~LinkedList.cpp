// FUNC_NAME: LinkedList::~LinkedList

int __thiscall LinkedList::~LinkedList(LinkedList *this, byte deleteFlag)
{
  // Release sub-object at offset +0x10 if present
  if (this->subObject != nullptr) {
    // FUN_004daf90 likely releases or destroys the sub-object
    subObject->release(reinterpret_cast<int>(&this->subObject)); // offset +0x10
  }

  // Set vtable pointer to current class's vtable for safety
  this->vtable = &g_LinkedListVTable; // PTR_FUN_00e32808

  // Clear the linked list starting at offset +0x0c
  LinkedListNode *currentNode = this->listHead; // +0x0c
  while (currentNode != nullptr) {
    LinkedListNode *nextNode = currentNode->next; // +0x04
    currentNode->next = nullptr;
    currentNode->data = nullptr; // +0x00
    currentNode = nextNode;
  }

  // If the delete flag (bit 0) is set, free this object's memory
  if ((deleteFlag & 1) != 0) {
    // FUN_009c8eb0 is likely operator delete or a memory deallocation function
    operatorDelete(this);
  }

  return reinterpret_cast<int>(this);
}
// FUNC_NAME: LinkedListNode::operator=
void __thiscall LinkedListNode::operator=(LinkedListNode *this, LinkedListNode *other)
{
  int *prevPtr;
  int otherPrev;
  
  // Copy the data value (first field)
  this->data = other->data;
  
  // Handle the prev pointer (offset +0x08)
  prevPtr = (int *)&this->prev;
  if (prevPtr != (int *)&other->prev) {
    otherPrev = other->prev;
    if (this->prev != otherPrev) {
      if (this->prev != 0) {
        // Remove this node from its current list by updating next pointer of previous node
        FUN_004daf90(prevPtr);  // likely: listRemoveNode or unlink
      }
      this->prev = otherPrev;
      if (otherPrev != 0) {
        // Update the next pointer of the previous node to point to this node
        this->next = *(int *)(otherPrev + 4);  // +0x04: next pointer in previous node
        *(int **)(otherPrev + 4) = prevPtr;   // update previous node's next to point to this
      }
    }
  }
  
  // Copy remaining fields
  this->field1 = other->field1;   // +0x04
  this->field4 = other->field4;   // +0x10
  this->field5 = other->field5;   // +0x14
  this->field6 = other->field6;   // +0x18
  this->field7 = other->field7;   // +0x1C
  this->field8 = other->field8;   // +0x20
}
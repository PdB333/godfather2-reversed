// FUNC_NAME: LinkedListNode::constructor
undefined4 * __thiscall LinkedListNode::constructor(undefined4 *this, byte flags)
{
  // Set vtable pointer
  *this = &PTR_FUN_00e433e8;
  
  // If next pointer is not null, update its prev pointer to point to our prev
  if (this[1] != 0) {
    *(undefined4 *)(this[1] + 8) = this[2];  // next->prev = this->prev
  }
  
  // If prev pointer is null, we're the head of the list
  if (this[2] == 0) {
    DAT_01205a54 = this[1];  // listHead = this->next
  }
  else {
    // Otherwise update prev's next pointer
    *(undefined4 *)(this[2] + 4) = this[1];  // prev->next = this->next
  }
  
  // If flag bit 0 is set, free the memory
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);  // operator delete
  }
  
  return this;
}
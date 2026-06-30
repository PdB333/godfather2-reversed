// FUNC_NAME: LinkedListNode::removeFromList
void __fastcall LinkedListNode::removeFromList(undefined4 *this)
{
  int *prevPtr;
  int *nextPtr;
  
  // Set vtable to first destructor
  *this = &PTR_FUN_00e37670;
  
  // If next node is null, update head pointer in global list
  if (this[0xc] == 0) {
    *(undefined4 *)(DAT_012234c8 + 4) = this[0xb]; // Update head to previous node
  }
  else {
    // Otherwise update next node's prev pointer
    *(undefined4 *)(this[0xc] + 0x2c) = this[0xb]; // next->prev = this->prev
  }
  
  // If previous node exists, update its next pointer
  if (this[0xb] != 0) {
    *(undefined4 *)(this[0xb] + 0x30) = this[0xc]; // prev->next = this->next
  }
  
  // Clear links
  this[0xb] = 0; // prev = null
  this[0xc] = 0; // next = null
  
  // Set vtable to second destructor
  *this = &PTR_FUN_00e37110;
  
  // If there's a pending deletion callback, add it to the deferred deletion list
  iVar1 = this[4]; // +0x10 - deletion callback
  if (iVar1 != 0) {
    piVar2 = (int *)(DAT_01206880 + 0x14); // Global deferred deletion list
    *(undefined ***)*piVar2 = &PTR_LAB_01123be8; // Add to list
    *piVar2 = *piVar2 + 4;
    *(int *)*piVar2 = iVar1;
    *piVar2 = *piVar2 + 4;
    this[4] = 0; // Clear callback
    this[5] = 0; // Clear callback data
  }
}
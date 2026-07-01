// FUNC_NAME: ListNode::ListNode
// Function at 0x0080e6a0: Constructor for a list node that computes container pointer from embedded member offset.
// Called from many places, likely a base class for intrusive linked list nodes.
// Offsets (in bytes from this):
//   +0x00: vtable pointer (set to PTR_LAB_00d72d5c)
//   +0x48: pointer to containing structure (if non-zero, used to compute container address)
//   +0x50: pointer to container (computed as containerPtr - 0x48)
//   +0x54: next pointer or flag (set to 0)

ListNode * __thiscall ListNode::ListNode(ListNode *this, void *param_2, void *param_3)
{
  // Call base class constructor or initializer (FUN_004ac120)
  FUN_004ac120(param_2, param_3);
  
  // Set vtable pointer
  this->vtable = (void **)PTR_LAB_00d72d5c;
  
  // If the embedded member pointer at +0x48 is non-null, compute the container address
  if (this->containerMemberPtr != 0) {
    this->containerPtr = (ListNode *)((char *)this->containerMemberPtr - 0x48);
    this->nextPtr = 0;
    return this;
  }
  
  // Otherwise, set both to null
  this->containerPtr = 0;
  this->nextPtr = 0;
  return this;
}
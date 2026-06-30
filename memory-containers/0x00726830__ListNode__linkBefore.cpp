// FUNC_NAME: ListNode::linkBefore
// Function at 0x00726830: Inserts 'this' node before the ListNode embedded at offset 0x48 in 'pObj'.
// The node structure is: +0x00 = next (ListNode*), +0x04 = prev (ListNode*).
// pObj is an object (e.g., Entity, GameObject) that contains a ListNode at offset 0x48.
// Calls FUN_004daf90 (ListNode::unlink) to detach 'this' from its current list if needed.

int* __thiscall ListNode::linkBefore(int* this, int* pObj)
{
  int* targetNode; // address of the target ListNode within pObj

  // Adjust param_2 to point to the ListNode inside the object
  if (pObj == (int*)0x0) {
    targetNode = (int*)0x0;
  }
  else {
    targetNode = (int*)((char*)pObj + 0x48);
  }

  // Only modify if 'this->next' is not already the target
  if (*this != (int)targetNode) {
    // If 'this' is currently linked, unlink it first
    if (*this != 0) {
      FUN_004daf90(this); // ListNode::unlink(this)
    }
    // Set 'this->next' to the target node
    *this = (int)targetNode;

    // If targetNode is non-null, link 'this' before it
    if (targetNode != (int*)0x0) {
      // Save targetNode's current prev into this->prev
      this[1] = *(int*)(targetNode + 1); // targetNode->prev
      // Set targetNode's prev to 'this'
      *(int**)((char*)targetNode + 4) = this; // targetNode->prev = this
    }
  }
  return this;
}
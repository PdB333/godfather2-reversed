// FUN_NAME: ListNode::unlinkFromList
// 00454ec0 - Removes this node from a doubly linked list. Writes the new head/tail pointers to output array.
// Offsets: +0x34 = next, +0x38 = prev
// Output: outResult[0] = the node that followed this (new head if this was head), outResult[1] = the node that preceded this (new tail if this was tail)
// Node's own links are cleared.

void __fastcall ListNode::unlinkFromList(ListNode** outResult)
{
  ListNode* next = this->next;
  ListNode* prev = this->prev;

  if (prev == 0) {
    // this was head: new head becomes next
    *outResult = next;
    if (next != 0) {
      next->prev = 0;
    }
  }
  else {
    // bypass this node
    prev->next = next;
  }

  if (next != 0) {
    // if next exists, fix its prev and clear this node
    next->prev = prev;
    this->next = 0;
    this->prev = 0;
    return;
  }

  // else this was tail: new tail becomes prev
  outResult[1] = prev;
  if (prev != 0) {
    prev->next = 0;
  }
  this->next = 0;
  this->prev = 0;
}
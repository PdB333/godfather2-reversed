// FUNC_NAME: ListNode::insertBefore
int * __thiscall ListNode::insertBefore(int *this, int *otherObject)
{
  int *targetNode;
  
  if (otherObject == (int *)0x0) {
    targetNode = (int *)0x0;
  }
  else {
    targetNode = (int *)((int)otherObject + 0x50); // +0x50: offset of ListNode field in containing object
  }
  if (this[0] != (int)targetNode) {
    if (this[0] != 0) {
      unlink(this); // FUN_004daf90: remove from current list
    }
    this[0] = (int)targetNode; // set next pointer
    if (targetNode != (int *)0x0) {
      this[1] = targetNode[1]; // set prev = target's prev
      targetNode[1] = (int)this; // set target's prev = this
    }
  }
  return this;
}
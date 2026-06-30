// FUNC_NAME: ListNode::attachToContainer
int * __thiscall ListNode::attachToContainer(int *this, void *container)
{
  int *listHead; // Pointer to the circular sentinel head node at container+0x48

  if (container == 0) {
    listHead = (int *)0;
  } else {
    listHead = (int *)((char *)container + 0x48); // +0x48: offset of sentinel head in container
  }
  if (*this != (int)listHead) { // If already in a different list, remove first
    if (*this != 0) {
      removeFromList(this); // FUN_004daf90: unlink from current list
    }
    *this = (int)listHead; // Set next pointer to head (circular)
    if (listHead != 0) {
      this[1] = *(listHead + 4); // Set prev to head's prev (old tail)
      *(listHead + 4) = (int)this; // Head's prev becomes this (insert at tail)
    }
  }
  return this;
}
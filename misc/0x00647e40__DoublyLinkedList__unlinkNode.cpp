// FUNC_NAME: DoublyLinkedList::unlinkNode
void DoublyLinkedList::unlinkNode(void)
{
  // Unlink this node from a doubly-linked list.
  // Assumes this is of type Node with fields:
  //   +0x18: next pointer
  //   +0x1c: prev pointer
  // The list head/root is at *(this + 0x18) when it is the head.
  
  // Set previous node's next to our next
  *(undefined4 *)(*(int *)(in_EAX + 0x18) + 0x1c) = *(undefined4 *)(in_EAX + 0x1c);
  // Set next node's prev to our prev
  *(undefined4 *)(*(int *)(in_EAX + 0x1c) + 0x18) = *(undefined4 *)(in_EAX + 0x18);
  return;
}
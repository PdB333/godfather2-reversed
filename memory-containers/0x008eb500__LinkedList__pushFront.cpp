// FUNC_NAME: LinkedList::pushFront
void __thiscall LinkedList::pushFront(int *listHead, int *node)
{
  // listHead points to the head pointer of a doubly-linked list (or singly with back pointer)
  // node is the new node to insert at the front
  // listHead[0] = head pointer
  // listHead[1] = tail pointer (only used when list is empty)
  // node[0] = next pointer (offset 0x00)
  // node[1] = prev pointer (offset 0x04)

  node[0] = *listHead;          // node->next = head
  node[1] = 0;                  // node->prev = NULL (new front)

  if (*listHead != 0) {
    // List is non-empty: update old head's prev to point to new node
    *(int **)(*listHead + 4) = node;
    *listHead = (int)node;      // head = node
    return;
  }

  // List was empty: set both head and tail to the new node
  listHead[1] = (int)node;      // tail = node
  *listHead = (int)node;        // head = node
  return;
}
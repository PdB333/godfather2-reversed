// FUNC_NAME: DoubleLinkedList::removeNode
uint __fastcall DoubleLinkedList::removeNode(uint *list, uint *node)
{
  uint *nextNode;
  uint result;
  
  result = in_EAX & 0xffffff00;
  if (*(short *)((int)list + 10) == 0) {
    return result;
  }
  if (node == (uint *)list[1]) { // node == tail
    result = *node; // next = node->next
    if (result != 0) {
      list[1] = result; // tail = next
      result = *node;
      *(undefined4 *)(result + 4) = 0; // next->prev = 0
      *(short *)((int)list + 10) = *(short *)((int)list + 10) + -1; // count--
      return CONCAT31((int3)(result >> 8),1);
    }
  }
  else {
    if (node != (uint *)*list) { // node != head
      *(uint *)(*node + 4) = node[1]; // node->prev->next = node->next
      nextNode = (uint *)node[1];
      *nextNode = *node; // node->next->prev = node->prev
      *(short *)((int)list + 10) = *(short *)((int)list + 10) + -1; // count--
      return CONCAT31((int3)((uint)nextNode >> 8),1);
    }
    if (node[1] != 0) { // node->next != 0
      result = node[1];
      *list = result; // head = node->next
      *(undefined4 *)node[1] = 0; // node->next->prev = 0
      *(short *)((int)list + 10) = *(short *)((int)list + 10) + -1; // count--
      return CONCAT31((int3)(result >> 8),1);
    }
  }
  *(short *)((int)list + 10) = *(short *)((int)list + 10) + -1; // count--
  list[1] = 0; // tail = 0
  *list = 0; // head = 0
  return CONCAT31((int3)(result >> 8),1);
}
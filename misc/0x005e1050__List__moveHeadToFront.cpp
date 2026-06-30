// FUNC_NAME: List::moveHeadToFront
void __thiscall List::moveHeadToFront(int *thisList, int *otherList)
{
  // thisList: pointer to list container (head at +0, tail at +4? or tail at +0x1c relative?)
  // otherList: pointer to another list container that has a pointer at +0x1c (likely a tail pointer holder)
  int *removedNode; // The node that is being moved, initially this->head
  int *newHead;     // The node that becomes the new head of this list (next of removed node)
  
  removedNode = (int *)*thisList;                        // this->head
  newHead = *(int **)((int)removedNode + 8);             // removedNode->next (offset +8)
  *thisList = (int)newHead;                              // this->head = newHead

  if (*(char *)((int)newHead + 0x15) == '\0') {          // Check flag at newHead+0x15
    *(int **)((int)newHead + 4) = thisList;              // newHead->prev = thisList (pointer to head variable)
  }
  *(int *)((int)removedNode + 4) = thisList[1];          // removedNode->prev = this->tail (offset +4)
  
  // Check if this list is empty (head == tail of other list? Actually compare thisList pointer with (* (otherList+0x1c) +4) value)
  if (thisList == *(int **)(*(int *)((int)otherList + 0x1c) + 4)) {
    // If this list is the one containing the tail, update tail to point to removedNode
    *(int *)(*(int *)((int)otherList + 0x1c) + 4) = (int)removedNode;
    *(int *)((int)removedNode + 8) = (int)thisList;      // removedNode->next = thisList (sentinel)
    thisList[1] = (int)removedNode;                      // this->tail = removedNode
    return;
  }
  
  // If not, update the previous node's next pointer
  int *prevNode = (int *)thisList[1];                    // this->tail (previous last node)
  if (thisList == *(int **)((int)prevNode + 8)) {        // If thisList is the head of prevNode's list? Actually check if thisList == prevNode->next (offset +8)
    *(int *)((int)prevNode + 8) = (int)removedNode;     // prevNode->next = removedNode
    *(int *)((int)removedNode + 8) = (int)thisList;     // removedNode->next = thisList
    thisList[1] = (int)removedNode;                     // this->tail = removedNode
    return;
  }
  
  // Otherwise, update prevNode->prev? Actually code sets *prevNode (as an int) to removedNode (offset +0?)
  *prevNode = (int)removedNode;                         // prevNode->prev? (offset +0) unclear
  *(int *)((int)removedNode + 8) = (int)thisList;      // removedNode->next = thisList
  thisList[1] = (int)removedNode;                      // this->tail = removedNode
  return;
}
// FUNC_NAME: LinkedList::transferNodes
int * __thiscall LinkedList::transferNodes(int *this, int *otherList)
{
  int *node;
  int *nextNode;
  int *currentNode;
  int temp;
  int *newNode;
  
  if (otherList == this) {
    return this;
  }
  // Remove all nodes from this list and free them
  node = (int *)*this;
  currentNode = (int *)0x0;
  if (node != (int *)0x0) {
    temp = *node;
    *this = temp;
    currentNode = node;
    if (temp == 0) {
      this[1] = 0; // tail = null
    }
    else {
      *(int *)(temp + 4) = 0; // prev of new head = null
      *node = 0;
    }
  }
  while (currentNode != (int *)0x0) {
    if (currentNode != (int *)0x0) {
      if (currentNode[8] != 0) {
        // Free data at offset +0x20 (8 * 4)
        FUN_004daf90(currentNode + 8);
      }
      // Free node itself
      FUN_009c8eb0(currentNode);
    }
    node = (int *)*this;
    currentNode = (int *)0x0;
    if (node != (int *)0x0) {
      temp = *node;
      *this = temp;
      currentNode = node;
      if (temp == 0) {
        this[1] = 0;
      }
      else {
        *(int *)(temp + 4) = 0;
        *node = 0;
      }
    }
  }
  // Transfer all nodes from otherList to this list
  for (newNode = (int *)*otherList; newNode != (int *)0x0; newNode = (int *)*newNode) {
    temp = FUN_009c8e50(0x2c); // allocate 44 bytes
    if (temp == 0) {
      newNode = (int *)0x0;
    }
    else {
      newNode = (int *)FUN_008eacb0(newNode); // copy node
    }
    *newNode = 0;
    newNode[1] = this[1]; // prev = tail
    if ((int *)this[1] == (int *)0x0) {
      *this = (int)newNode; // head = newNode
    }
    else {
      *(int *)this[1] = newNode; // tail->next = newNode
    }
    this[1] = (int)newNode; // tail = newNode
  }
  return this;
}
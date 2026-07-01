// FUNC_NAME: LinkedList::insertNode
void __thiscall LinkedList::insertNode(int *this, int param_2, int param_3)
{
  int *newNode;
  
  newNode = (int *)FUN_009c8e50(0x10);  // allocate 16 bytes for node
  if (newNode == (int *)0x0) {
    newNode = (int *)0x0;
  }
  else {
    *newNode = 0;          // +0x00: next pointer
    newNode[1] = 0;        // +0x04: prev pointer
    newNode[2] = param_2;  // +0x08: data1
    newNode[3] = param_3;  // +0x0C: data2
  }
  *newNode = *this;        // new node's next = current head
  newNode[1] = 0;          // new node's prev = null (will be set below)
  if (*this == 0) {
    this[1] = (int)newNode; // if list empty, set tail = new node
  }
  else {
    *(int **)(*this + 4) = newNode; // else old head's prev = new node
  }
  *this = (int)newNode;    // head = new node
  if ((this[3] != -1) && (this[3] < param_3)) {
    this[3] = param_3;     // update max value if needed
  }
  return;
}
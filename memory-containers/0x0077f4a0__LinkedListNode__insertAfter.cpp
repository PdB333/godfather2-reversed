// FUNC_NAME: LinkedListNode::insertAfter
void __thiscall LinkedListNode::insertAfter(int this, int newNode)
{
  int *nextPtr = (int *)(this + 0x54); // +0x54: pointer to next node in linked list
  
  if (newNode == 0) {
    newNode = 0;
  }
  else {
    newNode = newNode + 0x48; // +0x48: offset to node's 'prev' pointer? Or node data start?
  }
  
  if (*nextPtr != newNode) {
    if (*nextPtr != 0) {
      FUN_004daf90(nextPtr); // likely unlink or remove node
    }
    *nextPtr = newNode;
    if (newNode != 0) {
      *(undefined4 *)(this + 0x58) = *(undefined4 *)(newNode + 4); // +0x58: prev pointer? Copy prev from newNode
      *(int **)(newNode + 4) = nextPtr; // set newNode's prev to point to this node's next pointer
    }
  }
}
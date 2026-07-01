// FUNC_NAME: SomeList::setHead
void __thiscall SomeList::setHead(int this, int newHead)
{
  int *headPtr = (int *)(this + 0x13c); // +0x13c: head pointer field
  int adjustedNewHead;
  
  if (newHead == 0) {
    adjustedNewHead = 0;
  }
  else {
    adjustedNewHead = newHead + 0x48; // +0x48: offset to node's prev pointer? or some link field
  }
  
  if (*headPtr != adjustedNewHead) {
    if (*headPtr != 0) {
      FUN_004daf90(headPtr); // likely a detach/unlink function
    }
    *headPtr = adjustedNewHead;
    if (adjustedNewHead != 0) {
      *(int *)(this + 0x140) = *(int *)(adjustedNewHead + 4); // +0x140: some next pointer? copy from node+4
      *(int **)(adjustedNewHead + 4) = headPtr; // set node's back pointer to headPtr
    }
  }
}
// FUNC_NAME: ObjectPool::clear
void __fastcall ObjectPool::clear(int *this)
{
  int *nextNode;
  int *currentNode;
  uint index;

  currentNode = **(int ***)(*this + 8);  // +0x8: head of linked list
  while (currentNode != 0) {
    nextNode = **(int ***)(currentNode + 8);  // +0x8: next pointer in node
    FUN_009c8f10(*(int **)(currentNode + 8));  // destructor for node data
    FUN_009c8eb0(currentNode);  // free node memory
    this[4] = this[4] + -1;  // +0x10: decrement count
    currentNode = nextNode;
  }
  index = 0;
  do {
    *(undefined4 *)(*(int *)(*this + 8) + index * 4) = 0;  // clear free list array
    index = index + 1;
  } while (index <= (uint)this[2]);  // +0x8: capacity
  this[1] = 0;  // +0x4: reset size/head index
  return;
}
// FUNC_NAME: LinkedList::insertNodeAfter
void __thiscall LinkedList::insertNodeAfter(int this, int newNode)
{
  int* prevNextPtr;
  
  // Increment node count stored at +0x28
  *(int *)(this + 0x28) = *(int *)(this + 0x28) + 1;
  
  // Store current next pointer at newNode+8
  *(undefined4 *)(newNode + 8) = *(undefined4 *)(this + 0xc);
  
  // Set newNode's prev pointer to point to this+8 (the 'next' field of previous node)
  prevNextPtr = (int *)(newNode + 4);
  *prevNextPtr = this + 8;
  
  // Update the previous node's next pointer to point to newNode's prev field
  *(int **)(this + 0xc) = prevNextPtr;
  
  // Update the next node's prev pointer to point to newNode's prev field
  **(undefined4 **)(newNode + 8) = prevNextPtr;
}
// FUNC_NAME: LinkedListNode::insertAfter
void __thiscall LinkedListNode::insertAfter(int this, int newNode)
{
  int **prevNextPtr; // Pointer to the "next" field of the previous node (or head)
  
  // Get the address of the "next" pointer at offset +0x134
  prevNextPtr = (int **)(this + 0x134);
  
  // If newNode is the head (0), treat it as a null sentinel
  if (newNode == 0) {
    newNode = 0;
  }
  else {
    // The "prev" field of the new node is at +0x48
    newNode = newNode + 0x48;
  }
  
  // Only update if the "next" pointer would change
  if (*prevNextPtr != (int *)newNode) {
    // If there's an existing node after this one, detach it first
    if (*prevNextPtr != 0) {
      FUN_004daf90(prevNextPtr); // Probably ListDetach or similar
    }
    
    // Set this node's "next" to point to the new node (or null)
    *prevNextPtr = (int *)newNode;
    
    if (newNode != 0) {
      // Update the backward chain: the "next" field of the node before the new node 
      // now points to this node's insert position (+0x134)
      *(int *)(this + 0x138) = *(int *)(newNode + 4); // Save old next pointer
      *(int **)(newNode + 4) = prevNextPtr;           // Point back to our insertion point
    }
  }
}
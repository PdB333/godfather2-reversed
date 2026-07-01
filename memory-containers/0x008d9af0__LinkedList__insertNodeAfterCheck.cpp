// FUNC_NAME: LinkedList::insertNodeAfterCheck
void __fastcall LinkedList::insertNodeAfterCheck(int *listHead)
{
  int *nodePtr;
  int newNode;
  undefined4 someValue;
  int *prevNode;
  int stackTemp;
  undefined1 buffer [76];
  
  // Check if any of the four slots at listHead+0x7c through listHead+0x7f are non-zero
  // and the slot at listHead+0x81 is zero
  if (((((listHead[0x7c] != 0) || (listHead[0x7d] != 0)) || (listHead[0x7e] != 0)) ||
      (listHead[0x7f] != 0)) && (nodePtr = listHead + 0x81, listHead[0x81] == 0)) {
    // Get some value from a function
    someValue = FUN_00471610();
    // Initialize buffer with that value
    FUN_0044b4e0(buffer, someValue);
    // Call virtual function at vtable+0x58 (likely a method on the object)
    someValue = (**(code **)(*listHead + 0x58))(0, listHead, 0xffffffff, 0);
    // Allocate and initialize a new node
    prevNode = (int *)FUN_004df330(&stackTemp, listHead + 0x7c, buffer, someValue);
    // If the slot at listHead+0x81 already has a node, clear it
    if (*nodePtr != 0) {
      *(undefined4 *)(*nodePtr + 8) = 0;
      *nodePtr = 0;
    }
    // Link the new node into the list
    newNode = *prevNode;
    *nodePtr = newNode;
    if (newNode != 0) {
      *(int **)(newNode + 8) = nodePtr;  // Set prev pointer to point back to listHead+0x81
      *prevNode = 0;  // Clear the source pointer
    }
    // If there was a previous node in stackTemp, clear its prev pointer
    if (stackTemp != 0) {
      *(undefined4 *)(stackTemp + 8) = 0;
    }
  }
  return;
}
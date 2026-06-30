// FUNC_NAME: Entity::queueSpecialAction
void __fastcall Entity::queueSpecialAction(int *thisPtr)
{
  int *headPtr;
  int newNode;
  DWORD someValue;
  char buffer[76];
  int tempStack;

  // Check if any of the four flags at offsets 0x8d-0x90 are set and the list head is null
  if ((((thisPtr[0x8d] != 0) || (thisPtr[0x8e] != 0)) || (thisPtr[0x8f] != 0) || (thisPtr[0x90] != 0)) &&
      (headPtr = thisPtr + 0x95, *headPtr == 0)) {
    // Get a timestamp or identifier
    someValue = FUN_00471610();
    // Convert it to a buffer (e.g., format string)
    FUN_0044b4e0(buffer, someValue);
    // Call virtual function at vtable+0x58 (e.g., getSpecialActionID)
    DWORD actionID = (*(DWORD (**)(void *, int, int, int))(*thisPtr + 0x58))(0, thisPtr, -1, 0);
    // Allocate a new list node; the first argument is a pointer to store previous opposite node
    int *nodePtr = (int *)FUN_004df330(&tempStack, thisPtr + 0x8d, buffer, actionID);
    // Doubly linked list manipulation: insert node at front of list stored at this+0x95
    if (*headPtr != 0) {
      // Clear the previous pointer of the old head and set head to null (detach old head)
      *(int *)(*headPtr + 8) = 0;
      *headPtr = 0;
    }
    newNode = *nodePtr;
    *headPtr = newNode;
    if (newNode != 0) {
      // Set new node's previous pointer to the address of the head pointer
      *(int **)(newNode + 8) = headPtr;
      *nodePtr = 0;
    }
    if (tempStack != 0) {
      *(int *)(tempStack + 8) = 0;
    }
    // Set a flag indicating the action is pending (offset 0x74)
    thisPtr[0x74] |= 0x200;
  }
}
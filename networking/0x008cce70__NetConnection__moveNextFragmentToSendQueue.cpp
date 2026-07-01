// FUNC_NAME: NetConnection::moveNextFragmentToSendQueue
void __thiscall NetConnection::moveNextFragmentToSendQueue(NetConnection* this) {
  int* fragmentListHead;
  int* movedNode;
  int vtableResult;
  int dummyStack; // Possibly a pointer to store removed node's next pointer
  int stackFlag; // Not used otherwise

  // Check if any of the four source fragment list pointers are non-zero
  if (this->fragmentList1 != 0 || this->fragmentList2 != 0 ||
      this->fragmentList3 != 0 || this->fragmentList4 != 0) {
    // Call vtable function; likely returns a priority or node type
    vtableResult = (*(int (__thiscall**)(void))(
        *(int**)(*(int*)(this->vtablePtr + 8) + 8) + 4))();
    // Extract a fragment from the first source list (fragmentList1)
    movedNode = FUN_004df270(&dummyStack, &this->fragmentList1, vtableResult,
                             0x1ff, 0, &stackFlag);
    // Clear the current sent list head if any
    if (this->sentListHead != 0) {
      *((int*)this->sentListHead + 2) = 0; // Clear next pointer of old sent list head
      this->sentListHead = 0;
    }
    // Move the extracted node to the sent list head
    this->sentListHead = *movedNode; // Actually *movedNode is the node pointer
    if (this->sentListHead != 0) {
      *((int*)this->sentListHead + 2) = &this->sentListHead; // Set its "prev" pointer? Or next? offset +8
      *movedNode = 0; // Clear the source list head (root of the list)
    }
    // If dummyStack is non-zero, clear its next pointer (likely the old list head after removal)
    if (dummyStack != 0) {
      *((int*)dummyStack + 2) = 0;
    }
  }
  return;
}
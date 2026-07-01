// FUNC_NAME: ObjectPoolManager::allocateNode
void __fastcall ObjectPoolManager::allocateNode(ObjectPoolManager *this)
{
  int *freeNodePtr;
  int nodeAddr;
  int someValue;
  int *sourcePtr;
  int *newNode;

  // Check if any free slots are available
  if ((((this->m_freeSlotFlags[0] != 0) || (this->m_freeSlotFlags[1] != 0)) ||
      (this->m_freeSlotFlags[2] != 0)) || (this->m_freeSlotFlags[3] != 0)) {
    freeNodePtr = &this->m_freeListHead;  // pointer to head of free list
    sourcePtr = this;
    if (this->m_freeListHead != 0) {
      // Release the previous free node if any
      FUN_004df590();
    }
    // Virtual call to allocate or create something
    someValue = (*(int (__thiscall **)(void *, int, ObjectPoolManager *, int, int))(*(int *)this + 0x58))
                (0, this, 0, 0);
    someValue = FUN_00471610(someValue);
    // Allocate a new node from pool, returns pointer to pointer to node
    newNode = (int *)FUN_004df330(&sourcePtr, &this->m_freeSlotFlags, someValue);
    if (*freeNodePtr != 0) {
      // Clear previous node's backward pointer and detach it
      *(int *)(*freeNodePtr + 8) = 0;
      *freeNodePtr = 0;
    }
    nodeAddr = *newNode;  // Get the actual node address from the pool
    *freeNodePtr = nodeAddr;  // Set free head to this node
    if (nodeAddr != 0) {
      *(int **)(nodeAddr + 8) = freeNodePtr;  // Node's backward pointer points to head pointer
      *newNode = 0;  // Clear the pool's reference
    }
    if (sourcePtr != 0) {
      *(int *)(sourcePtr + 8) = 0;  // Clear node's backward pointer (detach from head)
    }
  }
}
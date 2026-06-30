// FUNC_NAME: PacketBufferPool::processCompletedNodes
void PacketBufferPool::processCompletedNodes(void)
{
  BufferNode* pNode;
  BufferNode* pNext;
  bool bAnyFreed;
  int* piVar9;

  pNode = *(BufferNode**)(this + 0x54); // current node pointer
  bAnyFreed = false;
  if (pNode == (BufferNode*)0x0) {
    return;
  }
LAB_004d0940:
  pNext = pNode->next; // save next node
  if (pNode->state == 6) { // state indicating completion?
    // Remove node from active list (doubly linked list managed by this)
    if (pNode->prev == (BufferNode*)0x0) {
      // Node is head of active list
      *(BufferNode**)(this + 0x54) = pNode->next; // update head
      if (pNode->next != (BufferNode*)0x0) {
        pNode->next->prev = (BufferNode*)0x0; // new head has no prev
        goto LAB_004d096e;
      }
    }
    else {
      pNode->prev->next = pNode->next; // bypass node in list
LAB_004d096e:
      if (pNode->next != (BufferNode*)0x0) {
        pNode->next->prev = pNode->prev; // fix back link
        goto LAB_004d0988;
      }
    }
    // If node was tail, update tail pointer
    BufferNode* pTemp = (BufferNode*)pNode->prev; // actually pNode->prev after removal? Wait code: puVar2 = piVar10[1]; then *(this+0x58)=puVar2. So pNode->prev is tail pointer for the list?
    *(BufferNode**)(this + 0x58) = pTemp; // update tail (offset 0x58)
    if (pTemp != (BufferNode*)0x0) {
      pTemp->prev = (BufferNode*)0x0; // tail has no next? Actually set to 0.
    }
LAB_004d0988:
    pNode->prev = (BufferNode*)0x0;
    pNode->next = (BufferNode*)0x0;

    // Process ring buffer of objects with reference counts
    do {
      piVar9 = (int*)pNode->ringBufferCurrent; // +0x33
      if (piVar9 == (int*)0x0) {
        EnterCriticalSection(&pNode->nodeCritSec); // +0x3a (critical section)
        if (pNode->ringBufferCount != 0) { // +0x39
          // Fetch next item from ring buffer
          pNode->ringBufferCurrent = *(int**)(pNode->ringBufferBase + pNode->ringBufferIndex * 4); // base +0x36, index +0x38
          pNode->ringBufferIndex = pNode->ringBufferIndex + 1;
          if (pNode->ringBufferSize <= pNode->ringBufferIndex) { // size +0x37
            pNode->ringBufferIndex = 0;
          }
          pNode->ringBufferCount = pNode->ringBufferCount - 1;
        }
        LeaveCriticalSection(&pNode->nodeCritSec);
        piVar9 = (int*)pNode->ringBufferCurrent;
        if (piVar9 == (int*)0x0) goto LAB_004d0a41;
      }
      // Decrement reference count on the object
      *piVar9 = *piVar9 - 1;
      if (*piVar9 == 0) {
        // Object is now free; return it to the pool's free list
        EnterCriticalSection((LPCRITICAL_SECTION)(this + 0x28)); // pool critical section
        int idx = *(int*)(this + 0x24); // free list write index
        int size = *(int*)(this + 0x1c); // free list size
        if (idx < size) {
          int pos = *(int*)(this + 0x20) + idx; // base + index
          *(int*)(this + 0x24) = idx + 1;
          if (pos >= size) {
            pos = pos - size; // wrap around
          }
          *(int**)(*(int*)(this + 0x18) + pos * 4) = piVar9; // store in free list
        }
        LeaveCriticalSection((LPCRITICAL_SECTION)(this + 0x28));
        bAnyFreed = true;
      }
      pNode->ringBufferCurrent = (int*)0x0; // clear fetched pointer
    } while( true );

LAB_004d0a41:
    // Cleanup callback object if present
    if (pNode->callbackObj != (void*)0x0) { // +0x42
      // Call destructor via vtable (vtable at this+0x94, offset 8)
      (**(code**)(**(int**)(this + 0x94) + 8))(pNode->callbackObj);
      pNode->callbackObj = (void*)0x0;
    }

    // Process a linked list of objects that need cleanup (refcount handling)
    int* pCleanup = (int*)pNode->cleanupList; // +0x44
    if (pCleanup != (int*)0x0) {
      do {
        uint* pObj = (uint*)pCleanup[1]; // next in cleanup list?
        int* pNextCleanup = (int*)*pCleanup; // save next
        if (pObj != (uint*)0x0) {
          if (*pObj < 2) {
            // No more references, destroy
            (**(code**)(**(int**)(this + 0x94) + 8))(pObj);
          }
          else {
            *pObj = *pObj - 1; // decrement reference
          }
          pCleanup[1] = 0; // clear pointer
        }
        // Return pCleanup to the pool's free list (head at this+0x10, tail at this+0x14)
        *pCleanup = *(int*)(this + 0x10);
        if (*(int*)(this + 0x10) == 0) {
          *(int**)(this + 0x14) = pCleanup;
        }
        *(int**)(this + 0x10) = pCleanup;
        pCleanup = pNextCleanup;
      } while (pNextCleanup != (int*)0x0);
      pNode->cleanupList = (int*)0x0;
      pNode->field_0x45 = 0; // +0x45
    }

    // Reset node state
    pNode->field_0x02 = 0; // byte at offset 8? Actually +0x02? That's weird. Code: *(undefined1 *)(piVar10 + 2) = 0; Since piVar10 is int*, +2 means offset 8 bytes.
    pNode->field_0x2a = 0; // +0x2a
    pNode->field_0x2b = -1; // +0x2b
    pNode->state = -0x67; // +0x2c, set to invalid state
    pNode->field_0x2d = 0;
    pNode->field_0x2f = 0;
    pNode->field_0x30 = 0;
    pNode->field_0x31 = 0;
    pNode->field_0x43 = 0;
    pNode->field_0x34 = 0; // +0x34

    // Insert node into the free list (doubly linked, head at this+0x5c, tail at this+0x60)
    pNode->next = *(BufferNode**)(this + 0x5c);
    pNode->prev = (BufferNode*)0x0;
    if (*(BufferNode**)(this + 0x5c) == (BufferNode*)0x0) {
      *(BufferNode**)(this + 0x60) = pNode; // tail = node
    }
    else {
      (*(BufferNode**)(this + 0x5c))->prev = pNode;
    }
    *(BufferNode**)(this + 0x5c) = pNode; // head = node
  }

  pNode = pNext;
  if (pNext == (BufferNode*)0x0) {
    if (!bAnyFreed) {
      return;
    }
    // Check if we need to trigger cleanup
    if (*(int*)(this + 0x48) == 0) {
      return;
    }
    if (*(int*)(*(int*)(this + 0x48) + 0xb0) != 2) {
      return;
    }
    FUN_004d1ab0(); // call to some cleanup/sweep function
    return;
  }
  goto LAB_004d0940;
}
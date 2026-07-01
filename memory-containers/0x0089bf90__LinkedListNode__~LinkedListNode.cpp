// FUNC_NAME: LinkedListNode::~LinkedListNode

int __thiscall LinkedListNode::~LinkedListNode(int this, byte flags)
{
  // Set vtable pointer at offset 0x28
  *(void***)(this + 0x28) = &PTR_LAB_00e317cc;

  // Remove this node from a doubly-linked list
  int* pPrev = *(int**)(this + 0x18);
  if (pPrev != nullptr) {
    int* pNext = *(int**)(this + 0x1c);
    int* pData = *(int**)(this + 0x20); // Possibly a data pointer or container
    if (pNext == nullptr) {
      // Update previous node's "next" (offset +0x04) to pData
      *(int*)(pPrev + 1) = (int)pData;
    } else {
      // Update next node's "prev" (offset +0x08) to pData
      *(int*)(pNext + 2) = (int)pData;
    }
    if (pData != nullptr) {
      // Update pData's "next" (offset +0x04) to pNext
      *(int*)(pData + 1) = (int)pNext;
    }
  }

  // Call base destructor
  FUN_0064d150();

  // If flag indicates deallocation, call operator delete
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  return this;
}
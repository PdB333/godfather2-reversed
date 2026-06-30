// FUNC_NAME: UnknownClass::~UnknownClass (destructor, resource deallocation)
void __thiscall UnknownClass::~UnknownClass(UnknownClass *this, byte flags)
{
  void *resource;
  int *freeListHead;
  int **freeListSlot;

  // Set vtable pointer (base class or virtual)
  *this = (UnknownClassVTable *)&PTR_FUN_00e37110;

  // If the resource handle (offset +0x10) is non-null
  resource = this->resourceHandle; // +0x10
  if (resource != 0) {
    // Access global free list manager: DAT_01206880 + 0x14 is a pointer to a linked list head
    freeListHead = *(int **)(DAT_01206880 + 0x14);
    freeListSlot = &PTR_LAB_01123be8; // Pre-existing list node pointer

    // Push current head onto free list (old head becomes next of new node)
    *freeListSlot = (int *)freeListHead;
    freeListHead = (int *)((char *)freeListHead + 4); // Advance to next free slot

    // Store the resource pointer into the free list
    *(void **)freeListHead = resource;
    freeListHead = (int *)((char *)freeListHead + 4); // Advance again

    // Clear the handle fields
    this->resourceHandle = 0;      // +0x10
    this->resourceHandle2 = 0;     // +0x14
  }

  // If the low bit of flags is set, free the memory itself (operator delete)
  if ((flags & 1) != 0) {
    operator delete(this);
  }
}
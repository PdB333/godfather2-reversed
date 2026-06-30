// FUNC_NAME: BaseArray::destructor (or similar array/metadata container destructor)
void __thiscall BaseArray_destructor(void *this)
// Purpose: Destroys a variable-length array with metadata stored at negative offsets.
// Structure layout (relative to 'this'):
//   this[-1] (?): likely size/count (in_EAX[-2] used as index)
//   this[0] (in_EAX+0?): pointer to allocation source? (first member)
//   this[3] (in_EAX[3]): pointer to an internal object (e.g., first element? or header?)
//   this[0xe] (in_EAX[0xe]): low word = count of secondary items (ushort), high word = flag?
//   this[0xf] (in_EAX[0xf]): pointer to secondary item array (each item size 0xC)
//   this[0x3e] (in_EAX[0x3e]): another pointer to a separate object
//   this[1] (?): reference counter? (accessed as *(int*)(this+4))
//   base pointer: maybe from a global heap/allocator at *this? (*(int*)(*this + 0xc) used)
{
  int *allocator; // base pointer to global allocator/manager
  int refCount;
  int itemPtr;
  unsigned int i;
  int secondaryItemBase;

  if (this == (void *)0x0) {
    return;
  }

  allocator = *(int **)this; // first DWORD is a pointer to allocation context (e.g., heap)
  itemPtr = *(int *)((int)this + 12); // this[3] — first object pointer

  if (itemPtr != 0) {
    // Clear pointer in allocator's table via offset derived from itemPtr -8 data
    *(undefined4 *)(*(int *)((int)allocator + 0xc) + *(int *)(itemPtr + -8) * 4) = 0;
    refCount = allocator[1];
    allocator[1] = refCount - 1;
    // Call a deallocation function (likely operator delete) on the object at itemPtr - 0x10
    (*(void (*)(void *))DAT_01206694)((void *)(itemPtr + -0x10));
  }

  i = (unsigned int)(unsigned short)(*(int *)((int)this + 0x38)); // this[0xe] low word (count)
  if (i != 0) {
    secondaryItemBase = *(int *)((int)this + 0x3c); // this[0xf] — pointer to array of items (size 0xC each)
    while (i > 0) {
      // Access items from the end: secondaryItemBase + (i-1)*0xC
      itemPtr = *(int *)(secondaryItemBase + -4 + i * 0xc); // effectively item at index i-1
      allocator = *(int **)this;
      if (itemPtr != 0) {
        *(undefined4 *)(*(int *)((int)allocator + 0xc) + *(int *)(itemPtr + -8) * 4) = 0;
        refCount = allocator[1];
        allocator[1] = refCount - 1;
        (*(void (*)(void *))DAT_01206694)((void *)(itemPtr + -0x10));
      }
      i--;
    }
  }

  // Also handle the base pointer of the secondary array itself if count > 0 and pointer exists
  if (((*(short *)((int)this + 0x38) != 0) && (itemPtr = *(int *)((int)this + 0x3c), itemPtr != 0)) {
    allocator = *(int **)this;
    *(undefined4 *)(*(int *)((int)allocator + 0xc) + *(int *)(itemPtr + -8) * 4) = 0;
    refCount = allocator[1];
    allocator[1] = refCount - 1;
    (*(void (*)(void *))DAT_01206694)((void *)(itemPtr + -0x10));
  }

  // Handle another separate pointer at this[0x3e]
  itemPtr = *(int *)((int)this + 0xf8); // this[0x3e]
  allocator = *(int **)this;
  if (itemPtr != 0) {
    *(undefined4 *)(*(int *)((int)allocator + 0xc) + *(int *)(itemPtr + -8) * 4) = 0;
    refCount = allocator[1];
    allocator[1] = refCount - 1;
    (*(void (*)(void *))DAT_01206694)((void *)(itemPtr + -0x10));
  }

  // Finally destruct the main object itself (referenced via negative index)
  allocator = *(int **)this;
  // Uses this[-2] as index: likely a slot number or serial
  *(undefined4 *)(*(int *)((int)allocator + 0xc) + *(int *)((int)this + -8) * 4) = 0;
  refCount = allocator[1];
  allocator[1] = refCount - 1;
  (*(void (*)(void *))DAT_01206694)((void *)((int)this + -16));
}
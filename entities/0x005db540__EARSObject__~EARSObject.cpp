// FUNC_NAME: EARSObject::~EARSObject
// Address: 0x005db540
// Base destructor for EARS engine objects. Sets vtable, frees child data,
// removes from temporary allocation list, then calls memory deallocation.

void __thiscall EARSObject::~EARSObject(EARSObject *this)
{
  int childPtr;
  undefined4 field_0x14;
  undefined4 field_0x10;
  int *allocatorPtr;
  undefined4 *ptrToThis;

  // Set vtable to destructor-only vtable to prevent virtual calls
  this->vtable = &VTable_EARSObject_DestructorOnly;

  childPtr = this->child; // +0x20
  if (childPtr != 0) {
    field_0x14 = this->field_0x14; // +0x14
    field_0x10 = this->field_0x10; // +0x10
    allocatorPtr = (int *)(gAllocator.List + 0x14); // DAT_01206880 -> list pointer + 0x14
    // Push data onto temporary allocation stack (3 values: child, field_0x10, field_0x14)
    **(int **)(gAllocator.List + 0x14) = &StackLabel_011273f4; // Some marker or control block
    *allocatorPtr = *allocatorPtr + 4;
    *(int *)*allocatorPtr = childPtr;
    *allocatorPtr = *allocatorPtr + 4;
    *(undefined4 *)*allocatorPtr = field_0x10;
    *allocatorPtr = *allocatorPtr + 4;
    *(undefined4 *)*allocatorPtr = field_0x14;
    *allocatorPtr = *allocatorPtr + 4;
  }

  if (this->deleter != 0) { // +0x18
    ptrToThis = this; // ?
    (*gDeleterCallback)(this->deleter); // DAT_0119caf4 – custom cleanup
  }

  ptrToThis = this;
  MEMORY_deallocate(&ptrToThis); // FUN_00423bf0 – frees the object memory
  MEMORY_cleanup(); // FUN_005d8600 – global allocator cleanup
  return;
}
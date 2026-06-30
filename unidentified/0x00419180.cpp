// FUN_00419180: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(SomeClass *this, byte isHeapAllocated)
{
  // Set vtable pointer (class virtual function table at 0x00e2fd10)
  this->vtable = &VTable_00e2fd10;
  
  // Call base class constructor (likely at 0x00418740)
  BaseClass::constructor(this);
  
  // If object was heap-allocated (flag bit 0 set),
  // call a custom deallocation function (operator delete or memory pool free)
  if ((isHeapAllocated & 1) != 0) {
    MemoryManager::deallocate(this);  // FUN_009c8eb0
  }
  
  return this;
}
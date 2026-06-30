// FUNC_ADDRESS: 0x004efd20 - EARSObject destructor (scalar deleting destructor)
// The destructor first releases a reference to an external object (offset +0x34),
// then calls the base destructor, and optionally deallocates the memory.

void __thiscall EARSObject::~EARSObject(EARSObject *this, byte deletingFlag)
{
  // Set vtable to current class's vtable (derived)
  this->vtablePtr = &PTR_FUN_00e373a4;
  
  // If there is a pointer at offset +0x34 (0xd * 4), set its value to 3
  // (likely a flag indicating release or 'orphaned' state) and clear the pointer.
  if (*(void **)((char *)this + 0x34) != (void *)0x0) {
    *(int *)*(void **)((char *)this + 0x34) = 3;
    *(void **)((char *)this + 0x34) = 0;
  }
  
  // Set vtable to base class's vtable (for proper destruction chain)
  this->vtablePtr = &PTR_LAB_00e37304;
  
  // If the calling convention indicates memory should be freed (bit 0 set), call operator delete
  if ((deletingFlag & 1) != 0) {
    FUN_009c8eb0(this);
  }
}
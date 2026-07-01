// FUNC_NAME: UnknownClass::constructor
undefined4 __thiscall UnknownClass_constructor(undefined4 this, byte flags) {
  int *vtablePtr;
  
  // Call base class constructor
  UnknownClass_baseConstructor();
  
  // Check if we should delete this object (flag bit 0 set)
  if ((flags & 1) != 0) {
    // Get vtable pointer and call virtual destructor at offset +0x04
    vtablePtr = (int *)getVtablePointer();
    (**(code **)(*vtablePtr + 4))(this, 0x50); // Call destructor with deallocation flag 0x50
  }
  
  return this;
}
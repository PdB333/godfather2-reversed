// FUNC_NAME: EARSObject::~EARSObject
undefined4 * __thiscall EARSObject::~EARSObject(undefined4 *this, byte flags)
{
  int childPtr;
  
  // Set vtable to derived class vtable (likely for this class)
  *this = &PTR_FUN_00d7c768;
  
  // Check if child object pointer at offset 0x2C is non-null
  if (this[0xb] != 0) {
    // Release or cleanup the child object
    FUN_004df590();
  }
  
  childPtr = this[0xb];
  if (childPtr != 0) {
    // Clear reference count or pointer at child+8
    *(undefined4 *)(childPtr + 8) = 0;
    this[0xb] = 0;
  }
  
  // Set vtable to base class vtable
  *this = &PTR_LAB_00e315b0;
  
  // Call base class destructor
  FUN_004149b0();
  
  // If flags has bit 0 set, free memory via operator delete
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}
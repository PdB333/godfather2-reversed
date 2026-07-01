// FUNC_NAME: EARSObject::destructor
undefined4 * __thiscall EARSObject::destructor(undefined4 *this, byte flags)
{
  // Set vtable pointer to base class vtable
  *this = &PTR_LAB_00d66080;
  
  // Call base destructor (likely for some component)
  FUN_007f6420(0);
  
  // Clear a bit in some flag field at offset +0x1f58 from this[0x17]
  // This clears bit 22 (0x400000) which is 0xffbfffff mask
  *(uint *)(this[0x17] + 0x1f58) = *(uint *)(this[0x17] + 0x1f58) & 0xffbfffff;
  
  // Set vtable pointer to another vtable (likely derived class)
  *this = &PTR_LAB_00d63090;
  
  // If there's a sub-object at this[0x1a], destroy it
  if (this[0x1a] != 0) {
    FUN_004daf90(this + 0x1a);
  }
  
  // Call some cleanup function
  FUN_0080ea60();
  
  // If the destructor was called with delete (bit 0 set), free memory
  if ((flags & 1) != 0) {
    FUN_00624da0(this);
  }
  
  return this;
}
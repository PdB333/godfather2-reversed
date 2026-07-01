// FUNC_NAME: EARSObject::~EARSObject
undefined4 * __thiscall EARSObject::~EARSObject(undefined4 *this, byte param_2)

{
  // +0x0: vtable pointer
  *this = &PTR_LAB_00d66008;  // Set to destructor vtable (second table)
  
  // +0x8C: flags field (bit 1 = something like "inManager" or "registered")
  if (((uint)this[0x23] >> 1 & 1) != 0) {
    // Call removeFromManager or unregister
    FUN_0072cb10(0);
  }
  
  // +0x0: vtable pointer (back to base class vtable)
  *this = &PTR_LAB_00d63090;
  
  // +0x68: some dynamically allocated member
  if (this[0x1a] != 0) {
    // Delete or release that member
    FUN_004daf90(this + 0x1a);
  }
  
  // Call base class destructor (EARS::Framework::Base or similar)
  FUN_0080ea60();
  
  // If param_2 (delete flag) has bit 0 set, operator delete this
  if ((param_2 & 1) != 0) {
    FUN_00624da0(this);
  }
  
  return this;
}
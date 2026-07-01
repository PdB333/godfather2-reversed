// FUNC_NAME: SomeClass::destructor
undefined4 * __fastcall SomeClass::destructor(undefined4 *this)
{
  uint flags;
  
  // Call base class destructor or cleanup
  SomeClass::baseDestructor();
  
  // Call virtual function at vtable+4 (likely release/delete)
  (**(code **)(*(int *)*this + 4))(this[6], 0x24);
  
  // Null out member at offset +0x18 (this[6])
  this[6] = 0;
  
  // Call another destructor/cleanup function
  SomeClass::cleanup();
  
  // Check if this was allocated with operator new (flag bit 0 set)
  if ((flags & 1) != 0) {
    // Free the memory
    operatorDelete(this);
  }
  
  return this;
}
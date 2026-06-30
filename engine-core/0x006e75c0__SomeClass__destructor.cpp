// FUNC_NAME: SomeClass::destructor
undefined4 * __thiscall SomeClass::destructor(undefined4 *this, byte flags)
{
  // Call base class destructor (likely EARSObject or similar)
  SomeBaseClass::destructor();
  
  // Call cleanup function on the first member (likely a vtable pointer or handle)
  cleanupFunction(*this);
  
  // If the 'flags' parameter has bit 0 set, free the memory (operator delete)
  if ((flags & 1) != 0) {
    operatorDelete(this);
  }
  
  return this;
}
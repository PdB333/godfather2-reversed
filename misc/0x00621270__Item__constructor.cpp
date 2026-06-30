// FUNC_NAME: Item::constructor
undefined4 __thiscall Item::constructor(Item *this,byte flags)

{
  // Call base class constructor (likely EARSObject or similar)
  EARSObject::constructor(this);
  
  // If the flag indicates custom cleanup is needed (bit 0), call the destructor
  // This pattern is typical for C++ new/delete placement and dtor chaining
  if ((flags & 1) != 0) {
    // Note: FUN_009c8eb0 is likely an operator delete or custom deallocation
    // Possibly derived class destructor or memory cleanup
    Item::destructor(this);
  }
  return this;
}
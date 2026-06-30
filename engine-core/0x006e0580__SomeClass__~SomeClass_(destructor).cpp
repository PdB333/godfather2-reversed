// FUNC_NAME: SomeClass::~SomeClass (destructor)
// Address: 0x006e0580
// Role: Destructor for a class of size 0x128 bytes (assuming 4-byte align). Contains cleanup of a member object at offset 0x68, base destructor call, and heap deallocation if the object was dynamically allocated.

// Note: The vtable pointers are set to special destructor vtables to ensure correct virtual dispatch during destruction.
// PTR_FUN_00d5f758, PTR_LAB_00d5f748, PTR_LAB_00d5f744, PTR_LAB_00d5f740 are likely addresses of destructor vtables.

undefined4 * __thiscall SomeClass::~SomeClass(SomeClass *this, byte param_2)
{
  // Set primary vtable pointer to destructor vtable
  this->vtable = &PTR_FUN_00d5f758;

  // Set secondary vtable pointers (for multiple inheritance or interface) to destructor vtables
  this->vtable2 = &PTR_LAB_00d5f748;        // +0x3C (offset 0x3C from this)
  this->vtable3 = &PTR_LAB_00d5f744;        // +0x48
  this->vtable4 = &PTR_LAB_00d5f740;        // +0x50

  // Check if a member object at offset +0x68 (param_1[0x1a]) exists; if so, call its destructor
  if (this->memberObject != 0)               // +0x68, a pointer to a sub-object
  {
    FUN_004daf90(&this->memberObject);        // destructor for that sub-object (takes address of pointer? But here passes &(this->memberObject) — likely a member destructor that cleans up the object)
  }

  // Call a global function (likely base class destructor or static cleanup)
  FUN_00473880();

  // If the object was heap-allocated (param_2 & 1), free its memory
  if ((param_2 & 1) != 0)
  {
    FUN_0043b960(this, 0x128);               // operator delete(this, size=0x128)
  }

  return this;
}
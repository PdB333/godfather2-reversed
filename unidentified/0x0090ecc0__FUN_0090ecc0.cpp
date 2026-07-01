// FUNC_NAME: SomeClass::SomeClass
// Constructor for a class of size 0xBC (188 bytes). 
// param_2: bit 0 indicates whether to call operator delete (FUN_0043b960) after base construction.
// This pattern is typical for placement new with custom memory management.
// Base constructor at 0x0090e920 initializes the base class portion.
// FUN_0043b960 is likely operator delete(void*, size_t) from the EARS memory system.

undefined4 __thiscall SomeClass::SomeClass(SomeClass *this, byte flag)
{
  // Call base class constructor
  BaseClass::BaseClass((BaseClass *)this);
  
  // If the low bit of flag is set, free the memory (e.g., for placement new failure or custom allocator)
  if ((flag & 1) != 0) {
    FUN_0043b960(this, 0xbc); // operator delete(this, 188)
  }
  
  return (undefined4)this;
}
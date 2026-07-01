// FUNC_NAME: SomeClass::constructor
undefined4 __thiscall SomeClass::constructor(SomeClass *this, byte flags)
{
  // Call base class constructor at 0x008f1520
  SomeBaseClass::constructor(this);
  
  // If bit 0 of flags is set, allocate 0x100 bytes (likely a buffer or array)
  if ((flags & 1) != 0) {
    // FUN_0043b960 is likely operator new or a memory allocation function
    // Allocate 0x100 bytes for this object
    operatorNew(this, 0x100);
  }
  
  return this;
}
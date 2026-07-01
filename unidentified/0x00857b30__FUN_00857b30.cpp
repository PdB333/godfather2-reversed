// FUNC_NAME: UnknownClass::constructor
undefined4 * __thiscall UnknownClass::constructor(undefined4 *this, byte param_2)
{
  // Set vtable pointers (two virtual function tables)
  *this = &PTR_LAB_00d751fc;  // +0x00: first vtable pointer
  this[1] = &PTR_LAB_00d751e8; // +0x04: second vtable pointer
  
  // Call base class constructor or initialization function
  FUN_0055a2a0();
  
  // If param_2 bit 0 is set, call destructor-like cleanup (placement delete)
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}
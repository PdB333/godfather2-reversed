// FUNC_NAME: BaseClass::~BaseClass
undefined4 * __thiscall BaseClass::~BaseClass(undefined4 *this, byte deletingFlag)
{
  // Set vtable pointer (likely to the class's vtable)
  *this = &PTR_FUN_00d7ab88;
  
  // Call base class destructor (or cleanup function)
  FUN_008b1cf0(this);
  
  // If member at offset +0x10 (param_1[4]) is not null, release it
  if (this[4] != 0) {
    FUN_009c8f10(this[4]); // release/destroy the member object
  }
  
  // Global cleanup/shutdown function
  FUN_00481520();
  
  // If the deleting flag (bit 0) is set, free the memory
  if ((deletingFlag & 1) != 0) {
    FUN_009c8eb0(this); // operator delete
  }
  
  return this;
}
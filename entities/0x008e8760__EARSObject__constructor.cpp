// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  // Call base class constructor at 0x008e86c0
  FUN_008e86c0();
  
  // If bit 0 of flags is set, allocate additional memory at offset 0x1b0
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0x1b0); // likely operator new or placement new for member at +0x1b0
  }
  
  return this;
}
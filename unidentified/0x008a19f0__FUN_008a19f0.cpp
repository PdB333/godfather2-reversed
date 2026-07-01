// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param_2, undefined4 param_3)
{
  // Call base class constructor or initializer
  FUN_004beb60(param_2, param_3);
  
  // Set vtable pointer
  *this = &PTR_FUN_00d78cf0;
  
  // Set additional function pointers
  this[3] = &PTR_LAB_00d78c58;
  this[4] = &PTR_LAB_00d78c50;
  
  // Initialize various fields to zero
  *(undefined1 *)(this + 0x50) = 0;  // +0x50: byte field
  *(undefined1 *)((int)this + 0x141) = 0;  // +0x141: byte field
  *(undefined1 *)((int)this + 0x142) = 0;  // +0x142: byte field
  this[0x51] = 0;  // +0x144: dword field
  
  // Call another initialization function
  FUN_00ad71a0();
  
  // Initialize more fields to zero
  *(undefined1 *)(this + 0x52) = 0;  // +0x148: byte field
  *(undefined1 *)(this + 0x72) = 0;  // +0x1C8: byte field
  *(undefined1 *)(this + 0x82) = 0;  // +0x208: byte field
  *(undefined1 *)(this + 0x8c) = 0;  // +0x230: byte field
  this[0x8d] = 0;  // +0x234: dword field
  
  // If global data pointer is non-null, copy data into this object
  if (DAT_01206940 != 0) {
    FUN_00408900(this, &DAT_01206940, 0x8000);  // memcpy-like copy of 0x8000 bytes
  }
  
  return this;
}
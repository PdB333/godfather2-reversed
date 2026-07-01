// FUNC_NAME: DataBufferObject::constructor
undefined4 * __thiscall DataBufferObject::constructor(DataBufferObject *this, undefined4 arg)
{
  // Call base class constructor (likely a common object base)
  BaseClass::constructor(arg);
  
  // Set up multiple vtable pointers (multiple inheritance or custom RTTI)
  this->vtable2 = &PTR_LAB_00e32854;          // +0x50 (offset 0x14*4)
  this->vtable  = &PTR_FUN_00d826fc;          // +0x00 (first vtable)
  this->vtable3 = &PTR_LAB_00d826ec;          // +0x3C (offset 0x0f*4)
  this->vtable4 = &PTR_LAB_00d826e8;          // +0x48 (offset 0x12*4)
  this->vtable2 = &PTR_LAB_00d826e4;          // +0x50 (overwrites previous vtable2)
  
  // Initialize fields to zero
  this->field_0x58 = 0;                       // +0x58 (int)
  *(undefined2 *)((uint)this + 0x5C) = 0;    // +0x5C (2 bytes)
  *(undefined2 *)((uint)this + 0x5E) = 0;    // +0x5E (2 bytes)
  this->field_0x60 = 0;                       // +0x60 (int)
  *(undefined2 *)((uint)this + 0x64) = 0;    // +0x64 (2 bytes)
  *(undefined2 *)((uint)this + 0x66) = 0;    // +0x66 (2 bytes)
  
  // If global data pointer is set, copy a large block (0x8000 bytes) into the object at offset 0x3C
  if (DAT_0120e93c != 0) {
    copyDataFromGlobal((uint *)this + 0x3C, &DAT_0120e93c, 0x8000);
  }
  
  return this;
}
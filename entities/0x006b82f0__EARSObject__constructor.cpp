// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, undefined4 param_2) {
  // Base class constructor call (likely EARS::Framework::Object or similar)
  BaseClass::BaseClass(param_2);
  
  // Virtual function table (vtable) at offset 0
  *this = &vtable_table;  // PTR_FUN_00d5e5b8
  
  // Additional vtable pointers (possibly for multiple inheritance)
  this[0xf] = &vtable_label1;  // +0x3C: points to another vtable or function ptr array
  this[0x12] = &vtable_label2; // +0x48: another vtable/interface
  
  // Zero out various member fields:
  this[0x14] = 0;       // +0x50: int
  *(short *)(this + 0x15) = 0;  // +0x54: short
  *(short *)((uint)this + 0x56) = 0; // +0x56: short
  this[0x16] = 0;       // +0x58: int
  this[0x17] = 0;       // +0x5C: int
  this[0x18] = 0;       // +0x60: int
  this[0x19] = 0;       // +0x64: int
  
  return this;
}
// FUNC_NAME: SomeClass::constructor

// Function at 0x006cfa70 - Constructor for an unknown class (likely UI or game object)
// Initializes multiple vtable pointers, zeros many fields, and calls sub-initializers

undefined4 * __thiscall SomeClass::constructor(SomeClass *this, undefined4 arg)

{
  // Likely base class constructor or initializer
  FUN_00473840(arg);
  
  // Set primary vtable pointer at offset 0x00
  *this = &PTR_FUN_00d5f228;
  
  // Set additional vtable/interface pointers at offsets 0x3C (0xF * 4), 0x48 (0x12 * 4), 0x50 (0x14 * 4)
  this->field_0x3C = &PTR_LAB_00d5f214;   // offset +0x3C
  this->field_0x48 = &PTR_LAB_00d5f210;   // offset +0x48
  this->field_0x50 = &PTR_LAB_00d5f20c;   // offset +0x50
  
  // Further initialization
  FUN_00473750();
  
  // Zero out fields at various offsets
  this->field_0xB4 = 0;                    // offset +0xB4 (0x2D * 4)
  *(short *)&this->field_0xB8 = 0;         // offset +0xB8 (0x2E * 4, 2 bytes)
  *(short *)((int)this + 0xBA) = 0;        // offset +0xBA (2 bytes)
  this->field_0xBC = 0;                    // offset +0xBC (0x2F * 4)
  *(short *)&this->field_0xC0 = 0;         // offset +0xC0 (0x30 * 4, 2 bytes)
  *(short *)((int)this + 0xC2) = 0;        // offset +0xC2 (2 bytes)
  this->field_0xC8 = 0;                    // offset +0xC8 (0x32 * 4)
  this->field_0xCC = 0;                    // offset +0xCC (0x33 * 4)
  this->field_0xD0 = 0;                    // offset +0xD0 (0x34 * 4)
  this->field_0xD4 = 0;                    // offset +0xD4 (0x35 * 4)
  
  // Static initializer call
  FUN_006cf1a0();
  
  // Registration or final initialization
  FUN_008a0d80(this);
  
  return this;
}
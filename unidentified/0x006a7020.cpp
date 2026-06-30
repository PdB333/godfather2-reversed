// FUN_NAME: EARSObject::Constructor
undefined4 * __thiscall EARSObject::Constructor(EARSObject *this, uint32_t param_2)
{
  // Call base class initialization (likely parent constructor) with unknown parameter
  FUN_0046c590(param_2);

  // Set vtable pointer (+0x00)
  *this = &EARSObject::vtable;

  // Set pointer fields at offsets +0x3C, +0x48
  this->field_0x3C = &PTR_LAB_00d5d800;  // +0x3C
  this->field_0x48 = &PTR_LAB_00d5d7fc;  // +0x48
  this->field_0x50 = 0;                  // +0x50

  // Zero out 2-byte fields at +0x54, +0x56
  *(uint16_t *)((uint8_t *)this + 0x54) = 0;
  *(uint16_t *)((uint8_t *)this + 0x56) = 0;

  this->field_0x58 = 0;                  // +0x58

  // Zero out 2-byte fields at +0x5C, +0x5E
  *(uint16_t *)((uint8_t *)this + 0x5C) = 0;
  *(uint16_t *)((uint8_t *)this + 0x5E) = 0;

  // Set debug/identifier magic values
  this->field_0x60 = 0xbadbadba;  // +0x60
  this->field_0x64 = 0xbeefbeef;  // +0x64
  this->field_0x68 = 0xeac15a55;  // +0x68
  this->field_0x6C = 0x91100911;  // +0x6C

  // Zero out remaining fields
  this->field_0x70 = 0;  // +0x70
  this->field_0x74 = 0;  // +0x74

  return this;
}
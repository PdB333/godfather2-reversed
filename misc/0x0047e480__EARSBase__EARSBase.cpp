// FUNC_NAME: EARSBase::EARSBase
undefined4 * __thiscall EARSBase::EARSBase(undefined4 param_2)
{
  // Call base class initializer
  FUN_0046c590(param_2);  // Possibly base constructor or memory setup

  // Set vtable pointer
  this->vtable = &PTR_FUN_00e33268;

  // Initialize unknown tables at offsets 0x3C and 0x48
  this->table0 = &PTR_LAB_00e33284;  // +0x3C
  this->table1 = &PTR_LAB_00e33294;  // +0x48

  // Debug sentinel values (EA EARS debug pattern)
  this->debugMarker1 = 0xbadbadba;  // +0x50
  this->debugMarker2 = 0xbeefbeef;  // +0x54
  this->debugMarker3 = 0xeac15a55;  // +0x58
  this->debugMarker4 = 0x91100911;  // +0x5C

  // Clear four unknown ints starting at +0x60
  this->unknown0 = 0;  // +0x60
  this->unknown1 = 0;  // +0x64
  this->unknown2 = 0;  // +0x68
  this->unknown3 = 0;  // +0x6C

  // Two shorts at +0x70 and +0x72, part of a larger field
  *(short *)&this->combinedField70_73 = 0;   // +0x70 (low 2 bytes)
  *(short *)((int)&this->combinedField70_73 + 2) = 0; // +0x72 (high 2 bytes)

  // Clear int at +0x74
  this->unknown4 = 0;  // +0x74

  return this;
}
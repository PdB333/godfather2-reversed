// FUNC_NAME: MultiTrackStream::constructor
undefined4 * __thiscall MultiTrackStream::constructor(MultiTrackStream *this, undefined4 param_2)
{
  undefined4 uVar1;
  undefined4 *vtablePtr; // temporary

  // Call base class constructor (likely StreamManager or similar)
  FUN_0046c590(param_2); // BaseClass::constructor(param_2)

  uVar1 = _DAT_00d5780c; // Some global constant, maybe a singleton or flag

  // Set vtable for this object
  this->vtable = &PTR_FUN_00d5fcd8; // Virtual function table

  // Initialize sub-object vtable pointers
  this->field_0x50 = &PTR_LAB_00e32854;   // +0x50: Sub-object vtable (later overwritten)
  this->field_0x3C = &PTR_LAB_00d5fcc8;   // +0x3C: Another vtable or interface
  this->field_0x48 = &PTR_LAB_00d5fcc4;   // +0x48: Yet another vtable

  // Overwrite field_0x50 with the correct vtable for this class
  this->field_0x50 = &PTR_LAB_00d5fcc0;   // +0x50: Correct sub-object vtable

  // Zero out a region from offset 0x54 to 0x68 (6 dwords)
  this->field_0x54 = 0; // +0x54
  this->field_0x58 = 0; // +0x58
  this->field_0x5C = 0; // +0x5C
  this->field_0x60 = 0; // +0x60
  this->field_0x64 = 0; // +0x64
  this->field_0x68 = 0; // +0x68

  // Zero out region from offset 0x84 to 0x9C (7 dwords)
  this->field_0x84 = 0; // +0x84
  this->field_0x88 = 0; // +0x88
  this->field_0x8C = 0; // +0x8C
  this->field_0x90 = 0; // +0x90
  this->field_0x94 = 0; // +0x94
  this->field_0x98 = 0; // +0x98
  this->field_0x9C = 0; // +0x9C

  // Set fields from global data
  this->field_0xA0 = uVar1;                // +0xA0: Some pointer or value from _DAT_00d5780c
  this->field_0xA4 = DAT_00d5fcbc;        // +0xA4: Another global constant
  *(byte *)((int)this + 0xA8) = 10;        // +0xA8: byte flag set to 10

  // Zero out region from offset 0x6C to 0x80 (6 dwords)
  this->field_0x6C = 0; // +0x6C
  this->field_0x70 = 0; // +0x70
  this->field_0x74 = 0; // +0x74
  this->field_0x78 = 0; // +0x78
  this->field_0x7C = 0; // +0x7C
  this->field_0x80 = 0; // +0x80

  // If the global buffer pointer is non-null, copy 0x8000 bytes into this object's internal buffer
  if (DAT_0120e93c != 0) {
    // Copy 32KB from global data to offset +0x3C (the buffer location)
    FUN_00408900(this->buffer, &DAT_0120e93c, 0x8000); // memcpy? Copies sound bank data
  }

  return this;
}
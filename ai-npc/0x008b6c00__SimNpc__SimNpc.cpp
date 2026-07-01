// FUNC_NAME: SimNpc::SimNpc
undefined4 * __thiscall SimNpc::SimNpc(SimNpc *this, undefined4 baseParam)
{
  // Call base class constructor (likely Sentient or Entity)
  Sentient::Sentient(baseParam); // FUN_008ba220

  // Set up vtable pointers for multiple inheritance
  this->vtable = &SimNpc_vtable_primary; // +0x00, PTR_FUN_00d7b238
  this->vtable_base1 = &SimNpc_vtable_base1; // +0x3C (offset 0xf), PTR_LAB_00d7b228
  this->vtable_base2 = &SimNpc_vtable_base2; // +0x48 (offset 0x12), PTR_LAB_00d7b224
  this->vtable_base3 = &SimNpc_vtable_base3; // +0x50 (offset 0x14), PTR_LAB_00d7b220
  this->vtable_base4 = &SimNpc_vtable_base4; // +0x54 (offset 0x15), PTR_LAB_00d7b1c0
  this->vtable_base5 = &SimNpc_vtable_base5; // +0x58 (offset 0x16), PTR_LAB_00d7b158
  this->vtable_base6 = &SimNpc_vtable_base6; // +0x180 (offset 0x60), PTR_LAB_00d7b140

  // Initialize various state fields
  this->field_a4 = 0;   // +0x290 (0xa4 * 4)
  this->field_a5 = 0;   // +0x294
  *(short *)&this->field_a6 = 0; // +0x298 (stored as 16-bit)
  *(short *)((int)this + 0x29a) = 0;  // +0x29a
  this->field_a7 = 0;   // +0x29c
  *(short *)&this->field_a8 = 0; // +0x2a0? Not sure at +0x2a0 (offset 0xa8?)
  *(short *)((int)this + 0x2a2) = 0; // +0x2a2
  *(byte *)&this->field_a9 = 0; // +0x2a4 (byte at offset 0xa9*4+?)
  this->field_aa = 0;  // +0x2a8
  this->field_ab = 0;  // +0x2ac

  // Debug/guard magic numbers (sentinel values)
  this->guardBad = 0xbadbadba;   // +0x2b0 (offset 0xac)
  this->guardBeef = 0xbeefbeef;   // +0x2b4 (offset 0xad)
  this->guardEars = 0xeac15a55;   // +0x2b8 (offset 0xae)
  this->guard911 = 0x91100911;    // +0x2bc (offset 0xaf)

  // If a global memory block exists, copy it into the object at +0x3C
  if (gSimNpcTemplate != (void *)0x0) {
    // Copy 0x8000 bytes from template into the base1 slot (likely state data)
    memcpy(&this->vtable_base1, gSimNpcTemplate, 0x8000); // FUN_00408900
  }

  return this;
}
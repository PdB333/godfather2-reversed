// FUNC_NAME: NetSession::constructor
undefined4 * __thiscall NetSession::constructor(NetSession *this, undefined4 param_2)
{
  undefined4 uVar1;
  
  // Call base class constructor (likely EARSObject or similar)
  EARSObject::constructor(param_2);
  
  // Set vtable pointer
  *this = &NetSession_vtable;
  
  // Initialize member fields - many zeroed out
  // +0x3c (0xf * 4): pointer to something
  this->field_0x3c = &NetSession_vtable_0x3c;
  // +0x48 (0x12 * 4): pointer to something
  this->field_0x48 = &NetSession_vtable_0x48;
  // +0x50 (0x14 * 4): zero
  this->field_0x50 = 0;
  // +0x54 (0x15 * 4): zero
  this->field_0x54 = 0;
  // +0x58 (0x16 * 4): zero
  this->field_0x58 = 0;
  // +0x5c (0x17 * 4): zero
  this->field_0x5c = 0;
  // +0x60 (0x18 * 4): zero
  this->field_0x60 = 0;
  // +0x64 (0x19 * 4): zero
  this->field_0x64 = 0;
  // +0x68 (0x1a * 4): zero
  this->field_0x68 = 0;
  // +0x6c (0x1b * 4): zero
  this->field_0x6c = 0;
  // +0x70 (0x1c * 4): zero
  this->field_0x70 = 0;
  // +0x74 (0x1d * 4): zero
  this->field_0x74 = 0;
  // +0xc0 (0x30 * 4): zero
  this->field_0xc0 = 0;
  // +0xc4 (0x31 * 4): zero
  this->field_0xc4 = 0;
  // +0xc8 (0x32 * 4): byte zero
  *(undefined1 *)(&this->field_0xc8) = 0;
  // +0xd8 (0x36 * 4): zero
  this->field_0xd8 = 0;
  // +0xd4 (0x35 * 4): zero
  this->field_0xd4 = 0;
  // +0xd0 (0x34 * 4): zero
  this->field_0xd0 = 0;
  // +0xcc (0x33 * 4): zero
  this->field_0xcc = 0;
  // +0xe8 (0x3a * 4): zero
  this->field_0xe8 = 0;
  // +0xe4 (0x39 * 4): zero
  this->field_0xe4 = 0;
  // +0xe0 (0x38 * 4): zero
  this->field_0xe0 = 0;
  // +0xdc (0x37 * 4): zero
  this->field_0xdc = 0;
  // +0xf8 (0x3e * 4): zero
  this->field_0xf8 = 0;
  // +0xf4 (0x3d * 4): zero
  this->field_0xf4 = 0;
  // +0xf0 (0x3c * 4): zero
  this->field_0xf0 = 0;
  // +0xec (0x3b * 4): zero
  this->field_0xec = 0;
  
  // Load global value for initial time/sequence
  uVar1 = _DAT_00d5780c;  // Some global time/sequence value
  
  // +0x108 (0x42 * 4): zero
  this->field_0x108 = 0;
  // +0x104 (0x41 * 4): zero
  this->field_0x104 = 0;
  // +0x100 (0x40 * 4): zero
  this->field_0x100 = 0;
  // +0xfc (0x3f * 4): zero
  this->field_0xfc = 0;
  // +0x10c (0x43 * 4): zero
  this->field_0x10c = 0;
  // +0x110 (0x44 * 4): short zero
  *(undefined2 *)(&this->field_0x110) = 0;
  // +0x112: short zero
  *(undefined2 *)((int)this + 0x112) = 0;
  // +0x114 (0x45 * 4): zero
  this->field_0x114 = 0;
  // +0x118 (0x46 * 4): short zero
  *(undefined2 *)(&this->field_0x118) = 0;
  // +0x11a: short zero
  *(undefined2 *)((int)this + 0x11a) = 0;
  // +0x11c (0x47 * 4): zero
  this->field_0x11c = 0;
  // +0x120 (0x48 * 4): short zero
  *(undefined2 *)(&this->field_0x120) = 0;
  // +0x122: short zero
  *(undefined2 *)((int)this + 0x122) = 0;
  // +0x124 (0x49 * 4): zero
  this->field_0x124 = 0;
  // +0x128 (0x4a * 4): short zero
  *(undefined2 *)(&this->field_0x128) = 0;
  // +0x12a: short zero
  *(undefined2 *)((int)this + 0x12a) = 0;
  
  // Set initial time/sequence values at various offsets
  // +0xbc (0x2f * 4): initial value
  this->field_0xbc = uVar1;
  // +0xa8 (0x2a * 4): initial value
  this->field_0xa8 = uVar1;
  // +0x94 (0x25 * 4): initial value
  this->field_0x94 = uVar1;
  // +0x80 (0x20 * 4): initial value
  this->field_0x80 = uVar1;
  
  // Zero out more fields
  // +0x8c (0x23 * 4): zero
  this->field_0x8c = 0;
  // +0x90 (0x24 * 4): zero
  this->field_0x90 = 0;
  // +0x88 (0x22 * 4): zero
  this->field_0x88 = 0;
  // +0x84 (0x21 * 4): zero
  this->field_0x84 = 0;
  // +0x9c (0x27 * 4): zero
  this->field_0x9c = 0;
  // +0xa4 (0x29 * 4): zero
  this->field_0xa4 = 0;
  // +0xa0 (0x28 * 4): zero
  this->field_0xa0 = 0;
  // +0x98 (0x26 * 4): zero
  this->field_0x98 = 0;
  // +0xac (0x2b * 4): zero
  this->field_0xac = 0;
  // +0xb8 (0x2e * 4): zero
  this->field_0xb8 = 0;
  // +0xb4 (0x2d * 4): zero
  this->field_0xb4 = 0;
  // +0xb0 (0x2c * 4): zero
  this->field_0xb0 = 0;
  
  // If there's a global data buffer, copy 0x8000 bytes into the structure
  if (DAT_0120e93c != 0) {
    FUN_00408900(this + 0xf, &DAT_0120e93c, 0x8000);
  }
  
  return this;
}
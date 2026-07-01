// FUNC_NAME: Color::constructor
undefined4 * __fastcall Color::constructor(undefined4 *this)
{
  undefined4 uVar1;
  
  uVar1 = _DAT_00d5780c;
  this[2] = 0;       // +0x08: alpha
  this[1] = 1;       // +0x04: red
  this[3] = &PTR_LAB_00d7312c; // +0x0C: vtable or something
  DAT_011298d4 = this;
  *this = &PTR_FUN_00d73134;   // +0x00: vtable pointer
  this[3] = &PTR_LAB_00d73130; // +0x0C: another ptr
  this[4] = 0;       // +0x10: ?
  this[5] = 1;       // +0x14: green?
  this[6] = 0;       // +0x18: ?
  this[7] = 0;       // +0x1C: blue?
  this[8] = 0;       // +0x20: ?
  this[0xd] = 0;     // +0x34: ?
  this[0xe] = 0;     // +0x38: ?
  this[0xf] = uVar1; // +0x3C: hue?
  this[0x10] = uVar1;// +0x40: saturation?
  this[0x15] = 1;    // +0x54: ?
  this[0x16] = 0;    // +0x58: ?
  this[9] = 0;       // +0x24: ?
  this[10] = 0;      // +0x28: ?
  this[0xb] = uVar1; // +0x2C: ?
  this[0xc] = uVar1; // +0x30: ?
  *(undefined1 *)(this + 0x12) = 0;           // +0x48: byte
  *(undefined1 *)((int)this + 0x49) = 0;      // +0x49: byte
  *(undefined1 *)((int)this + 0x4a) = 0;      // +0x4A: byte
  this[0x13] = 0;    // +0x4C: ?
  this[0x14] = 0;    // +0x50: ?
  *(undefined1 *)(this + 0x11) = 0xff;        // +0x44: byte = alpha (255)
  *(undefined1 *)((int)this + 0x45) = 0xff;   // +0x45: byte = red (255)
  *(undefined1 *)((int)this + 0x46) = 0xff;   // +0x46: byte = green (255)
  *(undefined1 *)((int)this + 0x47) = 0xff;   // +0x47: byte = blue (255)
  *(undefined1 *)((int)this + 0x4b) = 0xff;   // +0x4B: byte
  this[0x1b] = 0;    // +0x6C: ?
  this[0x1c] = 0;    // +0x70: ?
  this[0x1d] = uVar1;// +0x74: ?
  this[0x1e] = uVar1;// +0x78: ?
  this[0x23] = 1;    // +0x8C: ?
  this[0x24] = 0;    // +0x90: ?
  this[0x17] = 0;    // +0x5C: ?
  this[0x18] = 0;    // +0x60: ?
  this[0x19] = uVar1;// +0x64: ?
  this[0x1a] = uVar1;// +0x68: ?
  *(undefined1 *)(this + 0x1f) = 0xff;        // +0x7C: byte
  *(undefined1 *)((int)this + 0x7d) = 0xff;   // +0x7D: byte
  *(undefined1 *)((int)this + 0x7e) = 0xff;   // +0x7E: byte
  *(undefined1 *)((int)this + 0x7f) = 0xff;   // +0x7F: byte
  *(undefined1 *)(this + 0x20) = 0;           // +0x80: byte
  *(undefined1 *)((int)this + 0x81) = 0;      // +0x81: byte
  *(undefined1 *)((int)this + 0x82) = 0;      // +0x82: byte
  *(undefined1 *)((int)this + 0x83) = 0xff;   // +0x83: byte
  this[0x21] = 0;    // +0x84: ?
  this[0x22] = 0;    // +0x88: ?
  this[0x25] = 0;    // +0x94: ?
  if (DAT_012069c4 != 0) {
    // memcpy from global data
    FUN_00408900(this,&DAT_012069c4,0x8000);
  }
  if (DAT_01206978 != 0) {
    // memcpy from another global
    FUN_00408900(this,&DAT_01206978,0x8000);
  }
  return this;
}
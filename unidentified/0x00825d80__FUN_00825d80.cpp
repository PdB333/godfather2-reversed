// FUNC_NAME: SomeEARSObject::constructor
undefined4 * __thiscall SomeEARSObject::constructor(undefined4 *this, undefined4 param2)
{
  undefined4 someGlobal;
  
  FUN_0046c590(param2);
  someGlobal = DAT_00d5ccf8;
  *this = &PTR_FUN_00d73470;                    // vtable pointer
  this[0xf] = &PTR_LAB_00d73460;                // +0x3C: secondary vtable / function pointer
  this[0x12] = &PTR_LAB_00d7345c;               // +0x48: another function pointer
  this[0x14] = 0;                                // +0x50: some pointer/flag
  *(undefined2 *)(this + 0x15) = 0;              // +0x54: 16-bit value
  *(undefined2 *)((int)this + 0x56) = 0;         // +0x56: another 16-bit value
  this[0x16] = 0;                                // +0x58: pointer/flag
  this[0x17] = 0;                                // +0x5C: pointer/flag
  this[0x18] = 0;                                // +0x60: pointer/flag
  this[0x19] = 0;                                // +0x64: pointer/flag
  *(undefined1 *)((int)this + 0x6f) = 0;         // +0x6F: byte, probably end of a field
  this[0x1c] = 0;                                // +0x70: pointer/flag
  *(undefined2 *)(this + 0x1a) = 0xffff;         // +0x68: 16-bit, initialized to -1
  *(undefined2 *)((int)this + 0x6a) = 0xffff;    // +0x6A: 16-bit, initialized to -1
  *(undefined1 *)(this + 0x1b) = 0xff;           // +0x6C: byte, initialized to 0xFF
  *(undefined1 *)((int)this + 0x6d) = 0xff;      // +0x6D: byte, initialized to 0xFF
  *(undefined1 *)((int)this + 0x6e) = 0xff;      // +0x6E: byte, initialized to 0xFF
  this[0x1d] = someGlobal;                       // +0x74: stores global value from DAT_00d5ccf8
  this[0x1e] = 0xbadbadba;                       // +0x78: magic/sentinel value
  this[0x1f] = 0xbeefbeef;                       // +0x7C: magic/sentinel value
  this[0x20] = 0xeac15a55;                       // +0x80: magic/sentinel value (EA signature?)
  this[0x21] = 0x91100911;                       // +0x84: magic/sentinel value
  return this;
}
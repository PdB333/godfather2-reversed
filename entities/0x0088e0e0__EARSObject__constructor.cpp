// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor
  FUN_0046c590(param_2);
  
  // Set vtable pointer
  *this = &PTR_FUN_00d771a0;
  
  // Initialize member fields with sentinel values
  this[0xf] = &PTR_LAB_00d77190;  // +0x3C - some pointer
  this[0x12] = &PTR_LAB_00d7718c; // +0x48 - some pointer
  
  // Zero out various fields
  this[0x14] = 0;                 // +0x50
  *(undefined2 *)(this + 0x15) = 0; // +0x54 (2 bytes)
  *(undefined2 *)((int)this + 0x56) = 0; // +0x56 (2 bytes)
  this[0x16] = 0;                 // +0x58
  *(undefined2 *)(this + 0x17) = 0; // +0x5C (2 bytes)
  *(undefined2 *)((int)this + 0x5E) = 0; // +0x5E (2 bytes)
  this[0x18] = 0;                 // +0x60
  *(undefined2 *)(this + 0x19) = 0; // +0x64 (2 bytes)
  *(undefined2 *)((int)this + 0x66) = 0; // +0x66 (2 bytes)
  this[0x1a] = 0;                 // +0x68
  this[0x1b] = 0;                 // +0x6C
  this[0x1c] = 0xbadbadba;        // +0x70 - sentinel value
  this[0x1d] = 0xbeefbeef;        // +0x74 - sentinel value
  this[0x1e] = 0xeac15a55;        // +0x78 - sentinel value
  this[0x1f] = 0x91100911;        // +0x7C - sentinel value
  
  // Zero out byte fields
  *(undefined1 *)(this + 0x20) = 0;    // +0x80
  *(undefined1 *)((int)this + 0x81) = 0; // +0x81
  *(undefined1 *)((int)this + 0x82) = 0; // +0x82
  *(undefined1 *)((int)this + 0x83) = 0; // +0x83
  *(undefined1 *)(this + 0x21) = 0;     // +0x84
  
  return this;
}
// FUNC_NAME: PlayerSM::PlayerSM
undefined4 * __thiscall PlayerSM::PlayerSM(undefined4 *this, undefined4 param2, undefined4 param3)
{
  undefined4 uVar1;
  
  // Call base class constructor
  FUN_0080e6a0(param2, param3);
  
  // Set vtable pointer
  *this = &PTR_LAB_00d64d18;
  
  // Initialize flags and member variables
  *(undefined1 *)(this + 0x16) = 0;           // +0x58: byte flags
  this[0x17] = DAT_00d64d14;                  // +0x5C: some value
  this[0x18] = DAT_00d64d10;                  // +0x60: some value
  this[0x19] = 0;                              // +0x64: counter/flag
  this[0x1a] = 0;                              // +0x68: counter/flag
  this[0x1e] = 0;                              // +0x78: 
  this[0x1f] = 0;                              // +0x7C: 
  this[0x1d] = 0;                              // +0x74: 
  this[0x1c] = 0;                              // +0x70: 
  this[0x1b] = 0;                              // +0x6C: 
  
  // Check a flag in the associated object (at this[0x14] = +0x50 pointer to something)
  if ((*(uint *)(this[0x14] + 0x8e0) >> 1 & 1) == 0) {
    // Bit1 not set: clear flag at +0x58 bit0
    *(byte *)(this + 0x16) = *(byte *)(this + 0x16) & 0xfe;
    uVar1 = 0;
  }
  else {
    // Bit1 set: set flag at +0x58 bit0
    *(byte *)(this + 0x16) = *(byte *)(this + 0x16) | 1;
    uVar1 = 4;
  }
  
  // Call a virtual function on the associated object (vtable index 0x8D = 0x234/4)
  (**(code **)(*(int *)this[0x14] + 0x234))(uVar1, 1);
  
  // Set another flag based on bits from another field
  *(byte *)(this + 0x20) = (byte)((uint)*(undefined4 *)(this[0x14] + 0x8e8) >> 8) & 1;   // +0x80: byte
  return this;
}
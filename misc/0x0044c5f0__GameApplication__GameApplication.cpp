// FUNC_NAME: GameApplication::GameApplication
void __thiscall GameApplication::GameApplication(GameApplication *this)
{
  // Static globals: g_pApplication = this (0x012233b0)
  DAT_012233b0 = (undefined4 *)this;
  
  // vtable pointer at +0x00
  this[0x00] = &PTR_LAB_00e31624;
  
  // Copy two 4-byte values from globals at offsets +0x20 and +0x24 (indices 8 and 9)
  this[0x08] = DAT_00e445fc;   // +0x20
  this[0x09] = DAT_00e445f8;   // +0x24
  
  // Initialize flag field at +0x28 (index 10) to 0x80000000, then clear highest bit -> 0
  this[0x0a] = 0x80000000;
  this[0x0a] = this[0x0a] & 0x7fffffff;   // becomes 0
  
  // Zero out two 8-byte regions at +0x10..+0x17 and +0x18..+0x1F
  *(undefined8 *)(this + 4) = 0;       // +0x10..+0x17
  *(undefined8 *)(this + 6) = 0;       // +0x18..+0x1F
  
  // Additional zeroing of many fields
  this[0x12] = 0;    // +0x48 (index 18)
  this[0x0c] = 0;    // +0x30 (index 12)
  this[0x0f] = 0;    // +0x3C (index 15)
  this[0x0d] = 0;    // +0x34 (index 13)
  this[0x10] = 0;    // +0x40 (index 16)
  this[0x0e] = 0;    // +0x38 (index 14)
  this[0x11] = 0;    // +0x44 (index 17)
  
  // Set two consecutive bytes at +0x4C and +0x4D to 1
  *(byte *)(this + 0x13) = 1;          // offset 0x4C (index 19, low byte)
  *(byte *)((int)this + 0x4d) = 1;     // offset 0x4D
}
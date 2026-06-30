// FUNC_NAME: PlayerActionableInfo::constructor
undefined4 * __thiscall PlayerActionableInfo::constructor(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor at 0x006bd1d0
  FUN_006bd1d0(param_2);
  
  // Set vtable pointer (class-specific vtable at 0x00d5e668)
  *this = &PTR_FUN_00d5e668;
  
  // +0x3C (0xF*4): Pointer to some static data
  this[0xf] = &PTR_LAB_00d5e658;
  // +0x48 (0x12*4): Another static data pointer
  this[0x12] = &PTR_LAB_00d5e654;
  
  // +0x80 (0x20*4): Initialize various state flags to 0
  this[0x20] = 0;   // +0x80 - some flag
  this[0x22] = 0;   // +0x88 - some flag
  this[0x23] = 0;   // +0x8C - some flag
  this[0x24] = 0;   // +0x90 - some flag
  this[0x25] = 0;   // +0x94 - some flag
  
  // +0x84 (0x21*4): Set default value to 100
  this[0x21] = 100; // +0x84 - some timer/cooldown
  
  // +0x98 (0x26*4): Initialize more state
  this[0x26] = 0;   // +0x98 - some flag
  
  // +0x9C (0x27*2): Zero out 16-bit values
  *(undefined2 *)(this + 0x27) = 0;   // +0x9C - short value
  *(undefined2 *)((int)this + 0x9e) = 0; // +0x9E - short value
  
  // +0xAC to +0xBC (0x2B*4 down to 0x28*4): Zero out more state
  this[0x2b] = 0;   // +0xAC
  this[0x2a] = 0;   // +0xA8
  this[0x29] = 0;   // +0xA4
  this[0x28] = 0;   // +0xA0
  
  // +0xBC to +0xCC (0x2F*4 down to 0x2C*4): Zero out more state
  this[0x2f] = 0;   // +0xBC
  this[0x2e] = 0;   // +0xB8
  this[0x2d] = 0;   // +0xB4
  this[0x2c] = 0;   // +0xB0
  
  return this;
}
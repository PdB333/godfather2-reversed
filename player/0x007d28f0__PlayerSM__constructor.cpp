// FUNC_NAME: PlayerSM::constructor
undefined4 * __thiscall PlayerSM::constructor(undefined4 *this, undefined4 param_2, undefined4 param_3)
{
  // Call base class constructor (likely some state machine base)
  FUN_007ab5e0(param_2, param_3);
  
  // Set vtable pointer
  *this = &PTR_LAB_00d6ee6c;
  
  // Call some initialization function
  FUN_007d2590();
  
  // Initialize state machine variables
  this[0x2e] = 0;  // +0xB8 - some state index or timer
  this[0x2f] = 0;  // +0xBC - another state variable
  this[0x30] = 0;  // +0xC0 - state flag
  *(undefined1 *)(this + 0x2d) = 1;  // +0xB4 - set some byte flag to 1
  this[0x31] = 0;  // +0xC4 - another state variable
  
  // Set a flag at offset 0x28a0 in some sub-object at +0x58
  *(undefined1 *)(this[0x16] + 0x28a0) = 1;  // this+0x58->+0x28a0 = 1
  
  return this;
}
// FUNC_NAME: SimManager::constructor (or GodfatherGameManager::constructor? multiple vtable)
undefined4 * __thiscall SimManager::constructor(undefined4 *this, undefined4 arg1, undefined4 arg2)
{
  int derivedOffset;
  undefined4 globalValue;
  
  // Call base class constructor
  BaseClass::constructor(arg1, arg2);
  
  globalValue = g_globalSomeValue; // _DAT_00d63d70
  *this = &g_vtable1; // +0x00: primary vtable
  this[0x14] = &g_vtable2; // +0x50: secondary vtable (offset 20*4)
  this[0x40] = globalValue; // +0x100
  this[0x41] = 0; // +0x104
  
  // Compute derived pointer from self-referential offset at +0x48
  if (this[0x12] == 0) {
    derivedOffset = 0;
  } else {
    derivedOffset = this[0x12] - 0x48; // subtract offset to get base
  }
  this[0x43] = derivedOffset; // +0x10C
  
  if ((this[0x12] == 0) || (this[0x12] == 0x48)) {
    globalValue = 0;
  } else {
    globalValue = (*(code *)(DAT_01131038))(); // some function call (likely singleton getter)
  }
  this[0x42] = globalValue; // +0x108
  this[0x44] = 0xbdcf12bd; // +0x110: magic constant
  
  return this;
}
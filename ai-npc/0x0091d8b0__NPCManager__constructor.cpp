// FUNC_NAME: NPCManager::constructor

undefined4 * __fastcall NPCManager::constructor(undefined4 *this)

{
  FUN_005bf9b0(); // Base class constructor
  *this = &PTR_FUN_00d85be8; // vtable pointer
  this[4] = &PTR_LAB_00d85bc4; // Some member pointer
  this[0x13] = 0; // // +0x4C: member initialization to 0
  this[0x14] = 0; // // +0x50: member initialization to 0
  this[0x15] = 0; // // +0x54: member initialization to 0
  return this;
}
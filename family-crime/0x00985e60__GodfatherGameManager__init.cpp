// FUNC_NAME: GodfatherGameManager::init
undefined4* __fastcall GodfatherGameManager::init(undefined4* this)
{
  // Call base class initializer
  FUN_005bf9b0();

  // Set up vtable pointers and configuration fields

  // Offset +0x4c (0x13*4) - pointer to a static data block (initial, later overwritten)
  this[0x13] = &PTR_LAB_00d90bc8;

  // Store global pointer to this manager instance
  DAT_0112e228 = this;

  // Offset +0x54 (0x15*4) - initial value 0
  this[0x15] = 0;

  // Vtable pointer at offset 0
  *this = &PTR_FUN_00d90c78;

  // Offset +0x10 (4*4) - secondary vtable or interface pointer
  this[4] = &PTR_LAB_00d90c54;

  // Offset +0x4c (0x13*4) - overwrite with another data table pointer
  this[0x13] = &PTR_LAB_00d90c50;

  // Offset +0x50 (0x14*4) - version/config value 7
  this[0x14] = 7;

  // Offset +0x60 (0x18*4) - another config value 2
  this[0x18] = 2;

  // Offset +0x64 (0x19*4) - field set to -1 (0xFFFFFFFF)
  this[0x19] = 0xffffffff;

  // Offset +0x68 (0x1a*4) - short (2 bytes) set to 0
  *(undefined2 *)(this + 0x1a) = 0;

  // Offset +0x5c (0x17*4) - pointer from static data
  this[0x17] = PTR_DAT_00e575fc;

  // Offset +0x58 (0x16*4) - same static data pointer
  this[0x16] = PTR_DAT_00e575fc;

  return this;
}
// FUNC_NAME: InputManager::constructor
undefined4 * __fastcall InputManager::constructor(undefined4 *this)
{
  undefined1 *puVar1;
  
  FUN_005bf9b0();
  this[0x13] = &PTR_LAB_00d8d848; // vtable or data table at +0x4C
  _DAT_01130888 = this;
  *this = &PTR_FUN_00d8d878;
  this[4] = &PTR_LAB_00d8d850;   // +0x10
  this[0x13] = &PTR_LAB_00d8d84c; // +0x4C
  this[0x14] = 0;                 // +0x50: some counter/null
  this[0x16] = 0;                 // +0x58
  this[0x17] = 0;                 // +0x5C
  puVar1 = (undefined1 *)FUN_009c8e80(0x80); // malloc 128 bytes for controller state?
  this[0x15] = puVar1;            // +0x54: pointer to allocated buffer
  *puVar1 = 0;                    // initialize first byte to 0
  return this;
}
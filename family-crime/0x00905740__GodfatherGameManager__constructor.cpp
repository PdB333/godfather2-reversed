// FUNC_NAME: GodfatherGameManager::constructor
undefined4 * __fastcall GodfatherGameManager::constructor(undefined4 *this)
{
  undefined4 uVar1;
  
  DAT_01129894 = this;
  *this = &PTR_FUN_00d82660; // vtable pointer
  FUN_004c26c0(); // base class constructor
  this[1] = &PTR_FUN_00e36290; // vtable pointer for second base
  this[0x83] = 0; // +0x20C: some flag
  this[0x84] = 0; // +0x210: some flag
  this[0x85] = 0; // +0x214: some flag
  FUN_00905660(); // sub-object constructor
  FUN_004c26c0(); // base class constructor
  this[0x191] = 0; // +0x644: some flag
  this[0x192] = 0; // +0x648: some flag
  this[0x193] = 0; // +0x64C: some flag
  this[0x194] = &PTR_FUN_00e2f19c; // +0x650: vtable pointer
  this[0x195] = 1; // +0x654: some count
  this[0x196] = 0; // +0x658: some flag
  this[0x10f] = &PTR_FUN_00d82604; // +0x43C: vtable pointer
  this[0x194] = &PTR_LAB_00d825f4; // +0x650: data pointer
  FUN_004c26c0(); // base class constructor
  this[0x219] = 0; // +0x864: some flag
  this[0x21a] = 0; // +0x868: some flag
  this[0x21b] = 0; // +0x86C: some flag
  this[0x21c] = &PTR_FUN_00e2f19c; // +0x870: vtable pointer
  this[0x21d] = 1; // +0x874: some count
  this[0x21e] = 0; // +0x878: some flag
  this[0x197] = &PTR_FUN_00d825c0; // +0x65C: vtable pointer
  this[0x21c] = &PTR_LAB_00d825b0; // +0x870: data pointer
  uVar1 = FUN_00905970(); // sub-object constructor
  this[0x21f] = uVar1; // +0x87C: store result
  return this;
}
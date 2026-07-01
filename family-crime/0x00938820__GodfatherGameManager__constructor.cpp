// FUNC_NAME: GodfatherGameManager::constructor
undefined4 * __fastcall GodfatherGameManager::constructor(undefined4 *this)
{
  // Base class constructor call
  FUN_005bf9b0();
  
  // Initialize vtable pointers and member data
  this[0x13] = &PTR_LAB_00d8a45c;  // +0x4C - vtable pointer
  DAT_0112f948 = this;              // Store singleton pointer
  this[0x14] = &PTR_LAB_00e30fe0;  // +0x50 - vtable pointer
  *this = &PTR_FUN_00d8a4b0;       // +0x00 - primary vtable
  this[4] = &PTR_LAB_00d8a48c;     // +0x10 - vtable pointer
  this[0x13] = &PTR_LAB_00d8a488;  // +0x4C - vtable pointer (overwritten)
  this[0x14] = &PTR_LAB_00d8a478;  // +0x50 - vtable pointer (overwritten)
  this[0x15] = 0;                  // +0x54 - some pointer/flag
  this[0x16] = 0;                  // +0x58 - some pointer/flag
  this[0x17] = 0;                  // +0x5C - some pointer/flag
  this[0x18] = 0;                  // +0x60 - some pointer/flag
  *(undefined1 *)(this + 0x19) = 0; // +0x64 - byte field
  FUN_00407880(300);               // Allocate memory (300 bytes)
  FUN_00463980(0x460a9e80, this + 0x14, 7); // Initialize with float value and size
  
  return this;
}
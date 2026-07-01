// FUNC_NAME: GodfatherGameManager::constructor
void __fastcall GodfatherGameManager::constructor(GodfatherGameManager *this)
{
  // Call base class constructor (likely EARS::Framework::Object or similar)
  FUN_005bf9b0();
  
  // Set vtable pointer at +0x4C (0x13 * 4 = 0x4C)
  // PTR_LAB_00d8d950 is likely a vtable for a specific interface
  this[0x13] = &PTR_LAB_00d8d950;  // +0x4C: vtable pointer
  
  // Store global singleton pointer at 0x01130898
  _DAT_01130898 = this;  // Global singleton reference
  
  // Set main vtable pointer at +0x00
  *this = &PTR_FUN_00d8d980;  // +0x00: primary vtable
  
  // Set another vtable pointer at +0x10 (0x4 * 4 = 0x10)
  this[4] = &PTR_LAB_00d8d958;  // +0x10: secondary vtable
  
  // Re-set the vtable at +0x4C (possibly for a derived interface)
  this[0x13] = &PTR_LAB_00d8d954;  // +0x4C: tertiary vtable
  
  // Initialize a 16-bit field at +0x50 (0x14 * 4 = 0x50)
  *(uint16_t *)(this + 0x14) = 0;  // +0x50: some counter or flag (zeroed)
}
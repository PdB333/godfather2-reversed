// FUNC_NAME: GodfatherGameManager::initializeSingleton
void __fastcall GodfatherGameManager::initializeSingleton(GodfatherGameManager *this)
{
  // Set vtable pointer
  this->vtable = &PTR_FUN_00d8bb28; // +0x00: vtable pointer
  
  // Set other function pointers
  this->field_0x10 = &PTR_LAB_00d8bb04; // +0x10: some function pointer
  this->field_0x4c = &PTR_LAB_00d8bb00; // +0x4c: another function pointer
  this->field_0x4c = &PTR_LAB_00d8bafc; // +0x4c: overwritten with different pointer
  
  // Initialize global singleton flag
  DAT_01130004 = 0; // Global singleton instance pointer
  
  // Call initialization routine
  FUN_005c16e0(); // Likely GodfatherGameManager::init or similar
}
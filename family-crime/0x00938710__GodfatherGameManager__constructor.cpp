// FUNC_NAME: GodfatherGameManager::constructor
void __fastcall GodfatherGameManager::constructor(GodfatherGameManager *this)
{
  // Set vtable pointer
  this->vtable = &PTR_FUN_00d8a4b0; // +0x00: vtable pointer
  
  // Initialize member pointers
  this->field_0x10 = &PTR_LAB_00d8a48c; // +0x10: some pointer member
  this->field_0x4C = &PTR_LAB_00d8a488; // +0x4C: another pointer member
  this->field_0x50 = &PTR_LAB_00d8a478; // +0x50: yet another pointer member
  
  // Call initialization functions
  FUN_004639e0(0x460a9e80); // Likely some float/vector initialization (0x460a9e80 = 8760.0f?)
  FUN_00407430(); // Some initialization routine
  
  // Reassign pointers after initialization
  this->field_0x50 = &PTR_LAB_00e30fe0; // +0x50: reassigned
  this->field_0x4C = &PTR_LAB_00d8a45c; // +0x4C: reassigned
  
  // Clear global flag
  DAT_0112f948 = 0; // Global flag indicating something is not initialized
  
  // Final initialization call
  FUN_005c16e0(); // Likely final setup routine
}
// FUNC_NAME: GodfatherGameManager::constructor
undefined4 * __thiscall GodfatherGameManager__constructor(undefined4 *this, byte param_2)

{
  // Set vtable pointer
  *this = &PTR_FUN_00d82d2c;
  
  // Call base class constructor (likely SimManager or EARSObject)
  FUN_00906d50();
  
  // Initialize singleton instance (this[1] is a pointer to static singleton?)
  FUN_009c8f10(this[1]);
  
  // Update vtable to final vtable
  *this = &PTR_LAB_00d82940;
  
  // Clear global flag (DAT_01129888 - likely e.g. g_initialized or g_gameStarted)
  DAT_01129888 = 0;
  
  // If bit 0 of param_2 is set, call deallocator
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}
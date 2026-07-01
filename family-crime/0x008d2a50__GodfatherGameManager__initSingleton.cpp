// FUNC_NAME: GodfatherGameManager::initSingleton
void __fastcall GodfatherGameManager::initSingleton(GodfatherGameManager *this)
{
  // Set vtable pointer
  this->vtable = &PTR_FUN_00d7d420; // +0x00: vtable
  // Set state pointer to initial value
  this->state = &PTR_LAB_00d7d41c; // +0x0C: state pointer
  // Call some initialization function (likely mutex or singleton init)
  FUN_004086d0(&DAT_012069d4);
  // Update state pointer
  this->state = &PTR_LAB_00d7d418; // +0x0C: state pointer
  // Clear global singleton flag
  DAT_011299a0 = 0; // Global singleton initialized flag
  // Call cleanup/init function
  FUN_004083d0();
  return;
}
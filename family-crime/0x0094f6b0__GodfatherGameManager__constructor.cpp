// FUNC_NAME: GodfatherGameManager::constructor
void __fastcall GodfatherGameManager::constructor(GodfatherGameManager *this)
{
  // Set vtable pointer to GodfatherGameManager vtable
  this->vtable = &PTR_FUN_00d8baa8;
  // Set secondary vtable pointer
  this->secondaryVtable = &PTR_LAB_00d8ba98;
  
  // Call base class constructor (EARS::Framework::Object or similar)
  FUN_004086d0(&DAT_012069c4);
  
  // Initialize member variables
  this->field_0x18 = 0;  // +0x18
  this->field_0x1c = 0;  // +0x1c
  
  // Call initialization functions
  FUN_0094f610();  // Likely initializes game subsystems
  FUN_004083d0();  // Likely registers with manager or similar
  
  // Update vtable pointer to final vtable
  this->vtable = &PTR_LAB_00d8ba94;
  
  // Set global flag indicating game manager is initialized
  DAT_0112e2ec = 0;
  
  return;
}
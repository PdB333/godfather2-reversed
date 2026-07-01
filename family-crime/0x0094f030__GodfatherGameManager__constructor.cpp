// FUNC_NAME: GodfatherGameManager::constructor
void __fastcall GodfatherGameManager::constructor(GodfatherGameManager *this)
{
  char cVar1;
  
  // Set vtable pointer
  this->vtable = &PTR_FUN_00d8ba90;
  this->field_4 = &PTR_LAB_00d8ba80;
  
  // Check and release some global resource
  cVar1 = FUN_00402080(&DAT_012069c4);
  if (cVar1 != '\0') {
    FUN_004086d0(&DAT_012069c4);
  }
  
  // Initialize fields at +0x18 and +0x1C to 0
  this->field_18 = 0;
  this->field_1C = 0;
  
  // If pointer at +0x24 is non-null, release it
  if (this->field_24 != 0) {
    FUN_004daf90(&this->field_24);
  }
  
  // Call initialization functions
  FUN_0094ef90();
  FUN_004083d0();
  
  // Update vtable to final version
  this->vtable = &PTR_LAB_00d8ba7c;
  
  // Clear global flag
  DAT_011307ac = 0;
  
  return;
}
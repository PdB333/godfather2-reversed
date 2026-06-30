// FUNC_NAME: CharacterManager::constructor
void __fastcall CharacterManager::constructor(CharacterManager *this)
{
  // Set vtable pointer
  *this = &PTR_FUN_00e4448c;
  
  // Initialize field at +0x08 (likely a state or callback pointer)
  this->field_08 = &PTR_LAB_00e44498;
  
  // Call init function through vtable (offset 0x0C)
  (**(code **)(*(int *)(this->field_0C) + 0xC))();
  
  // Update field at +0x08 to different pointer
  this->field_08 = &PTR_LAB_00e4449c;
  
  // Reset global flag
  DAT_012234cc = 0;
  
  // Call base class or manager initialization
  FUN_0049c640();
  
  return;
}
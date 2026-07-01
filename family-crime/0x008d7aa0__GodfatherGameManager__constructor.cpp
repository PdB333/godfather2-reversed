// FUNC_NAME: GodfatherGameManager::constructor
undefined4 * __fastcall GodfatherGameManager::constructor(GodfatherGameManager *this)
{
  // Offset 0x04: some flag, set to 1 (possibly initialized or ref count)
  this->field_4 = 1;
  // Offset 0x08: zero
  this->field_8 = 0;
  // Offset 0x0c: pointer to static table (probably vtable? but it's set again later)
  this->field_0c = (void *)&PTR_LAB_00d7d6d8;
  // Store this singleton globally
  g_GodfatherGameManager = this;
  // Offset 0x00: virtual function table pointer
  this->vtable = (void *)&PTR_FUN_00d7d6f8;
  // Offset 0x0c: set to another static table (maybe second vtable)
  this->field_0c = (void *)&PTR_LAB_00d7d6f4;
  // Offset 0x2c to 0x40: zero out 6 words (0x2c, 0x30, 0x34, 0x38, 0x3c, 0x40)
  this->field_2c = 0;
  this->field_30 = 0;
  this->field_34 = 0;
  this->field_38 = 0;
  this->field_3c = 0;
  this->field_40 = 0;
  // Offset 0x10: zero
  this->field_10 = 0;
  // Initialize subsystems
  GodfatherGameManager::initAudio();   // FUN_008d7410
  GodfatherGameManager::initInput();   // FUN_008d74a0
  GodfatherGameManager::initPhysics(); // FUN_008d7550
  GodfatherGameManager::initScript();  // FUN_008d75e0
  // Offset 0x14: store global pointer (maybe database or config)
  this->field_14 = (void *)DAT_00d5ef50;
  // Final initialization
  GodfatherGameManager::initPostSubsystems(); // FUN_008d7040
  return this;
}
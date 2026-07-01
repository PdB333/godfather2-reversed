// FUNC_NAME: ConfigManager::isUnlocked
undefined4 ConfigManager::isUnlocked(float param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_004db3a0(param_1,"_UNLOCKED",9); // Get config value for key "_UNLOCKED"
  param_1 = 0.0;
  FUN_008934e0(uVar1,&param_1); // Convert to float
  if (param_1 != _DAT_00d577a0) { // Compare against default/zero value
    return 1; // Unlocked
  }
  return 0; // Locked
}
// FUNC_NAME: ViewSuppressionManager::suppressAllExceptSniperViewAndHealth
void __thiscall ViewSuppressionManager::suppressAllExceptSniperViewAndHealth(int this, char param_2)
{
  // Set flag at +0x5c bit 0x400 (likely "suppress all" flag)
  *(uint *)(this + 0x5c) |= 0x400;
  
  if (param_2 != '\0') {
    // When enabling, also set bit 0x40000000 (likely "allow sniper and health" flag)
    *(uint *)(this + 0x5c) |= 0x40000000;
    
    // Log suppression state
    FUN_005a04a0("SuppressAllExceptSniperViewAndHealth", 0, &DAT_00d8a64c, 0);
    
    // Probably reapply display or camera constraints
    FUN_005c1ad0();
    
    return;
  }
  
  // When disabling, call helper function to restore normal view
  FUN_0093c210();
  
  return;
}
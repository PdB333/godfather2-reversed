// FUNC_NAME: GodfatherGameManager::handlePlayerDeath
int __thiscall GodfatherGameManager::handlePlayerDeath(int this, int *param_2, int param_3)
{
  int iVar1;
  
  // Call virtual function at vtable+0x28 on param_3+0x90 (likely a death handler or cleanup)
  (**(code **)(*param_2 + 0x28))(param_3 + 0x90);
  
  // If there's a pending death-related object at +0x58, free it
  if (*(int *)(this + 0x58) != 0) {
    FUN_007ff260(*(int *)(this + 0x58));
  }
  
  // Get the global game manager singleton
  iVar1 = FUN_007351c0();
  
  // Set bit 0x10000000 on the game state flags at +0x5c (death flag)
  *(uint *)(iVar1 + 0x5c) = *(uint *)(iVar1 + 0x5c) | 0x10000000;
  
  // Set bit 0x200000 on param_2[0x7d6] (likely a mission/objective flag)
  param_2[0x7d6] = param_2[0x7d6] | 0x200000;
  
  return iVar1 + 0x5c;
}
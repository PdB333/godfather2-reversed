// FUNC_NAME: PlayerWeaponComponent::onReload
void __thiscall PlayerWeaponComponent::onReload(int this, int weapon)
{
  float fPlayerMultiplier;
  float fWeaponMultiplier;
  int iPlayerManager;
  int iWeaponComponent;
  int iPlayerState;
  char bIsMultiplayer;
  int iNetObject;
  int *pVtable;
  int iEventHandle1;
  int iEventHandle2;
  
  // Check flags: bit 17 in weapon's flags at +0x18c must be 0 (e.g., not already reloading?)
  if (((((((unsigned char)(*(unsigned int *)(weapon + 0x18c) >> 17) & 1) == 0) &&
        (*(int *)(*(int *)(this + 0x180) + 0xd8) != 0)) && // Some pointer validity
       (iPlayerManager = FUN_0043b870(DAT_0112afb8), iPlayerManager != 0)) &&
      (((iPlayerState = *(int *)(iPlayerManager + 0x1c), iPlayerState != 0 &&
        (iPlayerState != 0x3c)) &&
       ((iPlayerPtr = **(int **)(DAT_012233a0 + 4), iPlayerPtr != 0 &&
        ((iPlayerPtr != 0x1f30 && (iPlayerPtr != -0x794)))))))) && // Check not in certain game state
     // Check if reload timer should be reset (either below zero or sum below constant)
     ((*(float *)(iPlayerPtr + 0x804) < 0.0f ||
      (*(float *)(iPlayerState + 0xc0) + *(float *)(iPlayerPtr + 0x804) < DAT_01205228)))) {
    // Reset reload timer
    *(float *)(iPlayerPtr + 0x804) = DAT_01205228;
    
    // Calculate sound volume based on weapon's reload multiplier and player's multiplier
    fWeaponMultiplier = *(float *)(weapon + 0x190);
    fPlayerMultiplier = *(float *)(iPlayerState + 0x58);
    
    // Play reload sound effects
    FUN_0078b270(4); // Set audio category to reload
    FUN_0078b4b0(fWeaponMultiplier * fPlayerMultiplier, 0, 1); // Play sound with scaled volume
    FUN_00402050(&DAT_0112a588, 0); // Stop previous reload sound
    
    // Check for specific weapon components by hash
    iWeaponComponent = FUN_006ad790(weapon, 0x36cac259); // "AmmoComponent"?
    if (iWeaponComponent == 0) {
      iWeaponComponent = FUN_006ad7c0(weapon, 0x6a8acf44); // "WeaponComponent"?
      if ((iWeaponComponent != 0) && (bWeaponCheck = FUN_00690150(0x5d), bWeaponCheck != 0)) {
        // If certain weapon (ID 0x5d) is active, early return
        return;
      }
    }
    else if ((*(unsigned char *)(iWeaponComponent + 0x290) & 1) != 0) {
      // If ammo component has flag bit0 set, early return (already reloading?)
      return;
    }
    
    // Check if in multiplayer session
    bIsMultiplayer = FUN_00732380();
    if ((bIsMultiplayer != 0) && (**(int **)(DAT_012233a0 + 4) != 0)) {
      iPlayerPtr = **(int **)(DAT_012233a0 + 4) - 0x1f30; // Adjust pointer to net object base
      if (iPlayerPtr != 0) {
        pVtable = (int *)FUN_006ad7f0(iPlayerPtr); // Get vtable pointer
        (**(code **)(*pVtable + 0x28))(0x848db96, 0, 0xffffffff, 0); // Send net message?
        
        iEventHandle2 = 0;
        iEventHandle1 = FUN_006fbc40(0, 0); // Begin analytics event
        FUN_007f96a0(0x888ad614, 0x74, iEventHandle1, iEventHandle2); // Send "reload_start" event
        FUN_006fbc70(); // End analytics event
        
        bIsMultiplayer = FUN_0078a7d0();
        if (bIsMultiplayer != 0) {
          iEventHandle2 = 0;
          iEventHandle1 = FUN_006fbc40(0, 0);
          FUN_007f96a0(0x8908c696, 0x74, iEventHandle1, iEventHandle2); // Send "reload_end" event
          FUN_006fbc70();
        }
      }
    }
  }
  return;
}
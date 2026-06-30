// FUNC_NAME: PlayerState::canUseWeapon
// Function at 0x007341f0 checks if the player is allowed to perform a weapon-based action (shoot/attack).
// Returns 1 if allowed, 0 otherwise.

// Assume these are known offsets in the Player object (relative to this pointer).
// Offsets in bytes: 
// +0x1F54 (0x7d5*4) -> playerFlags
// +0x2004 (0x801*4) -> currentWeaponId
// +0x8E4 (0x239*4) -> combatStateFlags
// +0x8E0 (0x238*4) -> aimStateFlags
// +0x1E70 (0x79c*4) -> unknownFlag (e.g., bIsInVehicle)
// +0x5F4 (0x17d*4) -> pActiveTarget

// Global game manager pointer (stored in ESI by callers)
extern int* g_pGameManager; // unaff_ESI

// External helper functions with their roles:
bool isGameplayFlagEnabled(int flagId); // FUN_00690150: checks global gameplay flags
bool canReachTarget(int* pTarget);      // FUN_009af6f0: checks if target is reachable
bool isSomethingActive();               // FUN_007f7b90: unknown
bool canPerformCombatAction();          // FUN_00799b10: unknown

undefined1 __thiscall canUseWeapon(int* pThis, int* pTarget)
{
    char ret;
    float extraout_ST0;
    
    uVar2 = 0; // default return false
    
    // Check various conditions on the player object
    // Condition 1: bit 6 of playerFlags must be clear (e.g., not in a cutscene)
    if (((( ( (uint)pThis[0x7d5] >> 6 & 1 ) == 0 ) &&
          ( pThis[0x801] != 0 ) && // weaponId must be non-zero
          ( pThis[0x801] != 0x48 ) ) && // weaponId not "fists" (0x48)
         // Condition 2: virtual function at vtable+0xC0 returns a float > 0 (e.g., aim angle or distance)
         (( (**(code **)(*pThis + 0xc0))(), (float10)0 < extraout_ST0 &&
          ( (uint)pThis[0x239] >> 0x16 & 1 ) == 0 )) && // bit 22 of combatStateFlags clear (e.g., not reloading)
        ) &&
        // Condition 3: bit 4 of aimStateFlags clear
        (( ( (uint)pThis[0x238] >> 4 & 1 ) == 0 &&
          // Check global gameplay flags: 0x5c = fire weapon allowed?, 0x5d = another restriction
          ( ret = isGameplayFlagEnabled(0x5c), ret == '\0' ) &&
          ( ret = isGameplayFlagEnabled(0x5d), ret == '\0' )
          )) ) &&
        // Condition 4: check global flag 5 (e.g., is mission active?)
        (( ret = isGameplayFlagEnabled(5), ret == '\0' ) &&
         // Condition 5: player not in a vehicle (0x79c == 0) and has a target (0x17d != 0)
         ((( pThis[0x79c] == 0 && pThis[0x17d] != 0 ) &&
          // Target reachable check
          ( ret = canReachTarget(pTarget), uVar2 = 0, ret != '\0' )) &&
          // Virtual function at vtable+0x228 returns success? (e.g., can activate weapon)
          ( ret = (**(code **)(*pThis + 0x228))(pTarget), ret == '\0' ))))
    {
        uVar2 = 1; // temporary true
        // Now check target's component via interface query (hash 0x383225a1 = likely IID_WeaponComponent)
        ret = (**(code **)(*pTarget + 0x10))(0x383225a1, &stack0x00000000);
        if ((ret != '\0') && (g_pGameManager != 0)) {
            // If component found and game manager valid
            ret = isSomethingActive();
            if (((ret == '\0') ||
                // Or if gameManager->someFlags bit 2 set (0x8e4) and combat action allowed
                (( (*(uint*)(g_pGameManager + 0x8e4) >> 2 & 1 ) != 0 &&
                  ( ret = canPerformCombatAction(), ret != '\0' )))) &&
                // And gameManager->anotherFlags bit 10 clear (0x249c)
                (( *(uint*)(g_pGameManager + 0x249c) >> 10 & 1 ) == 0))
            {
                return 1;
            }
            uVar2 = 0;
        }
    }
    return uVar2;
}
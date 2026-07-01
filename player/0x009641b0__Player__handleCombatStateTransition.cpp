// FUNC_NAME: Player::handleCombatStateTransition
undefined4 __fastcall Player::handleCombatStateTransition(int thisPtr)

{
  // Check if combat flag bit 3 is set and bit 2 is clear
  // +0x6F4: combatStateFlags (bitfield)
  if ((((*(uint *)(thisPtr + 0x6f4) >> 3 & 1) != 0) && ((*(uint *)(thisPtr + 0x6f4) >> 2 & 1) == 0))
     // Check if current combat mode is 8 (e.g., aiming/attacking)
     && (*(int *)(DAT_012234b8 + 0x10) == 8)) {
    // Transition out of combat state
    FUN_00964070(); // Player::exitCombatMode
    FUN_00567c60(); // Player::resetWeaponState
    // Clear bit 3 (exit combat flag)
    *(uint *)(thisPtr + 0x6f4) = *(uint *)(thisPtr + 0x6f4) & 0xfffffff7;
    // Set bit 2 (combat transition complete)
    *(uint *)(thisPtr + 0x6f4) = *(uint *)(thisPtr + 0x6f4) | 4;
  }
  return 0;
}
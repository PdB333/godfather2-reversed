// FUNC_NAME: Player::resetState
void __fastcall Player::resetState(int thisPtr)
{
  *(uint8_t *)(thisPtr + 0x209) = 0; // +0x209: some flag (e.g., bIsDead, bIsDowned, bIsStunned)
  FUN_00873bb0(1); // likely Player::setInvulnerable(true) or similar
  FUN_0087f980(0); // likely Player::clearTarget or resetCombatState
  FUN_008742c0();  // likely Player::resetAnimationState or resetMovement
  if (*(int *)(thisPtr + 0x1b8) != 0) { // +0x1b8: pointer to some owned object (e.g., weapon, item, vehicle)
    FUN_005e6820(*(int *)(thisPtr + 0x1b8), 0, 0); // detach or release owned object
    FUN_005e6660(*(int *)(thisPtr + 0x1b8)); // delete or free owned object
    *(int *)(thisPtr + 0x1b8) = 0; // clear pointer
  }
}
// FUNC_NAME: Player::setInCombatState
void __thiscall Player::setInCombatState(int this, char isEnteringCombat, char isImmediate)
{
  // +0x5fc: combatStateCounter (int) - tracks number of combat state requests
  // +0x1b94: flags (uint) - bitfield for various player states
  // +0x5f8: combatTimer (float) - timer for combat state duration
  // DAT_01205228: some global combat duration constant

  if (isEnteringCombat == '\0') {
    // Exiting combat: decrement counter if non-zero
    if (*(int *)(this + 0x5fc) != 0) {
      *(int *)(this + 0x5fc) = *(int *)(this + 0x5fc) + -1;
    }
  }
  else {
    // Entering combat: increment counter
    *(int *)(this + 0x5fc) = *(int *)(this + 0x5fc) + 1;
    if (isImmediate != '\0') {
      // Immediate combat: set flag bit 0x200000 and reset timer
      *(uint *)(this + 0x1b94) = *(uint *)(this + 0x1b94) | 0x200000;
      *(undefined4 *)(this + 0x5f8) = DAT_01205228;
    }
  }

  if (*(int *)(this + 0x5fc) == 0) {
    // No more combat requests: clear combat flags (bits 17-19)
    *(uint *)(this + 0x1b94) = *(uint *)(this + 0x1b94) & 0xfff9ffff;
    return;
  }

  // Still in combat: set combat flags (bits 17-18 = 0x60000)
  *(uint *)(this + 0x1b94) = *(uint *)(this + 0x1b94) | 0x60000;
  return;
}
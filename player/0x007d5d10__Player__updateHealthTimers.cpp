// FUNC_NAME: Player::updateHealthTimers
void __thiscall Player::updateHealthTimers(int thisPtr, float deltaTime)
{
  int iVar1;
  uint timerIndex;
  uint offset;
  float fVar4;
  float fVar5;
  
  timerIndex = 9;
  offset = 0x54;
  do {
    fVar4 = DAT_00d5e288; // Default value (likely a constant like 0.0f or max health)
    // Check if the timer at index is disabled via a bitmask at this+0x58->+0x249c
    if ((*(uint *)(*(int *)(thisPtr + 0x58) + 0x249c + (timerIndex >> 5) * 4) & 1 << ((byte)timerIndex & 0x1f)) == 0) {
      // Timer is active: decrease it by deltaTime, clamp to 0
      fVar4 = *(float *)(*(int *)(thisPtr + 0x74) + offset) - deltaTime;
      if (fVar4 < 0.0) {
        fVar4 = 0.0;
      }
      *(float *)(*(int *)(thisPtr + 0x74) + offset) = fVar4;
    }
    else {
      // Timer is disabled: increase it by deltaTime, but cap at some max value
      iVar1 = *(int *)(*(int *)(thisPtr + 0x58) + 0x1c78);
      fVar5 = *(float *)(*(int *)(thisPtr + 0x74) + offset) + deltaTime;
      if ((iVar1 == 0) || (iVar1 == 0x48)) goto LAB_007d5de4;
      iVar1 = FUN_0043b870(DAT_0112afb8); // Likely getPlayer() or getGameManager()
      if ((iVar1 == 0) || ((iVar1 = *(int *)(iVar1 + 0x1c), iVar1 == 0 || (iVar1 == 0x3c)))) {
switchD_007d5da5_caseD_d:
      }
      else {
        // Look up max value based on timer index from some player stats
        switch(timerIndex) {
        case 9: // Health regen timer
          fVar4 = *(float *)(iVar1 + 0xa4); // +0xA4: maxHealthRegenTime?
          break;
        case 10: // Armor regen timer
          fVar4 = *(float *)(iVar1 + 0xa8); // +0xA8: maxArmorRegenTime?
          break;
        case 0xb: // Stamina regen timer
          fVar4 = *(float *)(iVar1 + 0xac); // +0xAC: maxStaminaRegenTime?
          break;
        case 0xc: // Special ability timer
          fVar4 = *(float *)(iVar1 + 0xb0); // +0xB0: maxSpecialAbilityTime?
          break;
        default:
          goto switchD_007d5da5_caseD_d;
        case 0xf: // Another timer (maybe adrenaline?)
          fVar4 = *(float *)(iVar1 + 0xbc); // +0xBC: maxAdrenalineTime?
        }
      }
LAB_007d5de4:
      if (fVar4 <= fVar5) {
        // Cap reached: set timer to max and mark as ready (store some flag)
        *(undefined4 *)(*(int *)(thisPtr + 0x74) + -0x20 + offset) =
             *(undefined4 *)(*(int *)(thisPtr + 0x58) + 0x2108); // +0x2108: some ready flag value
        fVar5 = fVar4;
      }
      *(float *)(offset + *(int *)(thisPtr + 0x74)) = fVar5;
    }
    offset = offset + 4;
    timerIndex = timerIndex + 1;
    if (0x6f < offset) { // Loop through 7 timers (0x54 to 0x6F inclusive, step 4)
      return;
    }
  } while( true );
}
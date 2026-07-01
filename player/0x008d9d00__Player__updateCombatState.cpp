// FUNC_NAME: Player::updateCombatState
void __fastcall Player::updateCombatState(int *this)
{
  undefined8 uVar1;
  uint uVar2;
  char cVar3;
  int iVar4;
  undefined1 *puVar5;
  float fVar6;
  float local_18;
  float fStack_14;
  float local_c;
  float fStack_8;
  
  // Check if player is alive (+0x180 = health/state flag), not in special state (+0x25C & 3 == 0)
  // Increment some timer at +0x1C8, check if even frame
  // Check if some state at +0x1B8 is non-zero and not 0x48 (maybe cover state)
  // Check if bit 5 of +0x25C is set (maybe aiming flag)
  if ((((((char)this[0x60] != '\0') && ((this[0x97] & 3U) == 0)) &&
       (this[0x72] = this[0x72] + 1, (*(byte *)(this + 0x72) & 1) == 0)) &&
      ((this[0x6e] != 0 && (this[0x6e] != 0x48)))) && (((uint)this[0x97] >> 5 & 1) != 0)) {
    // Get camera position and rotation
    iVar4 = FUN_00471610(); // GetCameraManager
    uVar1 = *(undefined8 *)(iVar4 + 0x30); // Camera position XZ
    fVar6 = *(float *)(iVar4 + 0x38); // Camera position Y
    iVar4 = FUN_00471610(); // GetCameraManager again
    fStack_14 = (float)((ulonglong)uVar1 >> 0x20); // Camera X
    fStack_8 = (float)((ulonglong)*(undefined8 *)(iVar4 + 0x30) >> 0x20); // Target X
    fStack_14 = fStack_14 - fStack_8; // Delta X
    // Check distance threshold (+0x1C4 = maxDistance, +0x1C0 = minDistance)
    if ((float)((uint)fStack_14 & DAT_00e44680) < (float)this[0x71] ||
        (float)((uint)fStack_14 & DAT_00e44680) == (float)this[0x71]) {
      local_18 = (float)uVar1; // Camera Z
      local_c = (float)*(undefined8 *)(iVar4 + 0x30); // Target Z
      fVar6 = fVar6 - *(float *)(iVar4 + 0x38); // Delta Y
      // Check squared distance vs threshold (+0x1C0 = squared distance threshold)
      if ((fVar6 * fVar6 + fStack_14 * fStack_14 + (local_18 - local_c) * (local_18 - local_c) <=
           (float)this[0x70]) && (cVar3 = FUN_006abda0(), uVar2 = DAT_01205224, cVar3 != '\0')) {
        // Check if already in combat state (+0x190 = combat state flag)
        if ((char)this[100] != '\0') {
          // Already in combat, stop any active sound (+0x198 = sound handle)
          if (this[0x66] != 0) {
            FUN_005e6660(this[0x66]); // StopSound
            this[0x66] = 0;
          }
          FUN_008d9190(); // EnterCombatState
          return;
        }
        // Check cooldown timer (+0x194 = lastCombatTime)
        if (DAT_01205224 <= (uint)this[0x65]) {
          return;
        }
        // Increment combat attempt counter (+0x1CC = combatAttempts)
        this[0x73] = this[0x73] + 1;
        this[0x65] = uVar2 + 5000; // Set cooldown to current time + 5 seconds
        // Limit attempts to 4 before giving up
        if ((uint)this[0x73] < 5) {
          puVar5 = (undefined1 *)this[0x8f]; // Sound name string
          if (puVar5 == (undefined1 *)0x0) {
            puVar5 = &DAT_0120546e; // Default sound
          }
          iVar4 = (**(code **)(*this + 0xac))(puVar5,0); // PlaySound
          this[0x66] = iVar4; // Store sound handle
          FUN_008d9af0(); // StartCombatTransition
          return;
        }
        FUN_006abb60(); // ResetCombatAttempts
        this[0x73] = 0;
        FUN_008d9190(); // EnterCombatState
        return;
      }
    }
    else {
      this[0x73] = 0; // Reset attempts if out of range
    }
    // Check if some other action is pending (+0x204 = actionPending)
    if (this[0x81] != 0) {
      FUN_004df600(); // ExecutePendingAction
      return;
    }
  }
  return;
}
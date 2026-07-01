// FUNC_NAME: SoundManager::playOneShot
void __thiscall FUN_0093ed50(int this, undefined4 *param_2, undefined4 param_3)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  int iVar4;
  
  // Check if the total active sounds count is less than 20 (max concurrent sounds)
  if (*(uint *)(this + 0x50) < 0x14) {
    // Check if sound bank is loaded and we're not in a muted state
    if ((*(int *)(this + 0x44) == 0) &&
       ((*(int *)(this + 0x40) == 0 || ((*(byte *)(this + 0x34) & 1) == 0)))) {
      // Play a generic/fallback sound if no specific sound is queued
      FUN_004de190();
    }
    puVar1 = *(undefined4 **)(this + 0x44);
    if (puVar1 != (undefined4 *)0x0) {
      uVar2 = *puVar1;
      // Increment active sound count, decrement pending sound queue count
      *(int *)(this + 0x20) = *(int *)(this + 0x20) + 1;
      *(int *)(this + 0x1c) = *(int *)(this + 0x1c) + -1;
      // Move to next pending sound
      *(undefined4 *)(this + 0x44) = uVar2;
      if (puVar1 != (undefined4 *)0x0) {
        puVar3 = (undefined1 *)*param_2;
        if (puVar3 == (undefined1 *)0x0) {
          // Use default sound name if none provided
          puVar3 = &DAT_0120546e; // default sound name string
        }
        // Load sound data with priority 1 and timeout 12000ms
        iVar4 = FUN_0093e1a0(puVar3, param_3, 1, 12000);
        if (iVar4 != 0) {
          // Start playback of the loaded sound
          FUN_0093e4c0(iVar4);
        }
      }
    }
  }
  return;
}
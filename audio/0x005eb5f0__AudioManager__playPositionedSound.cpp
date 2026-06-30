// FUNC_NAME: AudioManager::playPositionedSound
void __thiscall AudioManager::playPositionedSound(void *this, undefined4 param_2, undefined4 param_3, undefined4 param_4, int param_5, undefined4 param_6, byte param_7, byte param_8)
{
  uint uVar1;
  undefined4 local_98;
  undefined4 auStack_94 [36];
  
  // Initialize sound parameters structure
  local_98 = DAT_00e2b1a4; // Default sound flags / settings
  auStack_94[0x22] = 0;
  
  // Clear 16 entries of sound parameter array (likely for multi-channel or 3D positioning)
  uVar1 = 0;
  do {
    auStack_94[uVar1 * 2] = DAT_00e2b1a4; // Copy default flags
    auStack_94[uVar1 * 2 + 1] = 0;        // Clear second field (maybe volume/pan)
    uVar1 = uVar1 + 1;
  } while (uVar1 < 0x10);
  
  // Clear remaining two slots
  auStack_94[0x20] = 0;
  auStack_94[0x21] = 0;
  
  // Call internal sound playback function with scaled parameters
  // param_5 is scaled by DAT_00e2af48 (likely a distance/volume multiplier)
  // param_7 and param_8 are scaled by DAT_00e2af44 (likely pitch/pan multipliers)
  FUN_005eb6d0(param_1, param_2, param_3, param_4, 
               (float)param_5 * DAT_00e2af48, // Scaled distance/volume
               param_6,
               (float)param_7 * DAT_00e2af44, // Scaled pitch
               (float)param_8 * DAT_00e2af44, // Scaled pan
               &local_98,                     // Sound parameters structure
               96000,                         // Sample rate (96kHz)
               0);                            // Flags/priority
  return;
}
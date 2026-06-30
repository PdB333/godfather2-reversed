// FUNC_NAME: AudioManager::playSoundEffect
void __thiscall AudioManager::playSoundEffect(int param_1, int param_2)
{
  undefined4 uVar1;
  int *piVar2;
  undefined4 extraout_var;
  
  // Check if audio system is initialized (0x565 offset likely a state flag)
  if (*(char *)(DAT_012233b4 + 0x565) != '\x12') {
    // Validate sound index (param_2) is within range (0-14)
    if ((param_2 < 0xf) && (*(char *)(DAT_012233b4 + 0x565) != '\x12')) {
      // Get sound bank handle from audio system
      FUN_00411070(*(char *)(DAT_012233b4 + 0x565));
      // Play the sound effect
      FUN_004958a0(extraout_var);
    }
    // Get sound ID from lookup table (param_1 * 2 is index into sound ID table)
    uVar1 = (&DAT_01129bd0)[param_1 * 2];
    // Get audio system interface pointer
    piVar2 = (int *)FUN_00411070(*(undefined1 *)(DAT_012233b4 + 0x565));
    // Call virtual function at vtable+8 to play the sound
    (**(code **)(*piVar2 + 8))(uVar1);
  }
  return;
}
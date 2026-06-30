// FUNC_NAME: AudioManager::playSoundEffect
void __thiscall AudioManager::playSoundEffect(AudioManager* this)
{
  char soundKey[8]; // stack buffer for sound key
  int someGlobalConstant = DAT_00e2cd48; // global sound bank or volume constant
  int zero1 = 0;
  int zero2 = 0;

  if (*(int*)(this + 0xa8) != 0) // +0xA8: active flag or stream handle
  {
    // Build sound key from sound name (at +0x08) and sound data identifier (at +0xA4->+0x10)
    FUN_00c9cbe0(*(undefined4*)(this + 0x08), *(undefined4*)(*(int*)(this + 0xa4) + 0x10), 0, soundKey);
    // Setup local parameters
    soundKey[4] = someGlobalConstant;
    soundKey[8] = 0;
    soundKey[12] = 0;

    FUN_00c9eac0();                 // Start or prepare audio system
    FUN_00ca4e90(0, 0);            // Set volume/panning (both zero)
    FUN_00c9cd40(0, soundKey);     // Play the sound using the key
    FUN_00c9eae0();                 // Cleanup or finalize audio system
  }
}
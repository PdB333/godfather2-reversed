// Xbox PDB: EARS_Modules_Player_PlayFatigueAudio
// FUNC_NAME: FatigueSoundController::setActive
// Address: 0x0079f050
// Role: Toggles playing of a fatigue sound (sx_vox_herc_fatigue_01.emx)
// This function controls a single sound instance stored at offset 0xb1c,
// with an active flag at offset 0xb1d.

void __thiscall FatigueSoundController::setActive(int *this, char enable)
{
  int soundHandle;
  char buffer[16];  // unused buffer for sound loading
  void *temp1;      // unused, likely from macro
  int *temp2;       // unused

  if (enable == '\0')
  {
    // Disable: stop and release if currently playing
    if (this[0xb1c / 4] == 0)
    {
      return;
    }
    soundSystemStop(this[0xb1c / 4], 0, 0);        // FUN_005e6820
    soundSystemRelease(this[0xb1c / 4]);            // FUN_005e6660
    this[0xb1c / 4] = 0;                            // clear handle
  }
  else
  {
    // Enable: create new instance if not already playing
    if (this[0xb1c / 4] != 0)
    {
      return;
    }
    soundSystemPrepare();                            // FUN_005e3070
    temp1 = &LAB_0079f030;                           // unused label address
    temp2 = this;
    soundHandle = (**(code **)(*this + 0xac))("sx_vox_herc_fatigue_01.emx", buffer); // vcall LoadSound
    this[0xb1c / 4] = soundHandle;
    if (soundHandle != 0)
    {
      soundSystemSetVolume(soundHandle, DAT_00d5cf70); // FUN_005e6700, set volume from global
      *(unsigned char *)(this + (0xb1d / 4)) = 0;    // clear active flag (redundant)
      return;
    }
  }
  *(unsigned char *)(this + (0xb1d / 4)) = 0;        // set active flag to 0
  return;
}
// FUNC_NAME: AudioManager::playSound
void __fastcall AudioManager::playSound(undefined4 param_1, undefined4 param_2)
{
  // DAT_01125389 is likely a sound channel or category index
  // DAT_011254b8 is an array of sound instances, each 0x3c bytes
  // DAT_011252ec is the audio manager instance
  if (*(int *)(&DAT_011254b8 + (uint)DAT_01125389 * 0x3c) != 0) {
    FUN_0060add0(DAT_011252ec, *(int *)(&DAT_011254b8 + (uint)DAT_01125389 * 0x3c), param_2);
  }
  return;
}
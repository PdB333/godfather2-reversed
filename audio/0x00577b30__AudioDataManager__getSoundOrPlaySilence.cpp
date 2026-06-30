// FUNC_NAME: AudioDataManager::getSoundOrPlaySilence
undefined4 __fastcall AudioDataManager::getSoundOrPlaySilence(undefined4 *outResult, int soundIndex, int audioDataManager)
{
  undefined4 defaultVal;
  uint soundId;
  
  defaultVal = DAT_00e2b1a4;
  if (((*(int *)(audioDataManager + 0xb4) != 0) &&
      (soundId = (uint)*(byte *)(*(int *)(audioDataManager + 0xb4) + soundIndex), soundId != 0xff)) &&
     ((*(uint *)(audioDataManager + 0x10) >> 3 & 1) == 0)) {
    if (*(int *)(audioDataManager + 0xb8) != 0) {
      // Play the sound from the sound bank at the calculated offset
      FUN_00414c90(soundId * 0x40 + *(int *)(audioDataManager + 0xb8));
      return 1;
    }
    // Fallback: play silence or default sound
    FUN_00412d90(outResult);
    return 0;
  }
  // Sound not available or disabled, fill output with default values
  *outResult = DAT_00e2b1a4;
  outResult[1] = 0;
  outResult[2] = 0;
  outResult[3] = 0;
  outResult[4] = 0;
  outResult[5] = defaultVal;
  outResult[6] = 0;
  outResult[7] = 0;
  outResult[8] = 0;
  outResult[9] = 0;
  outResult[10] = defaultVal;
  outResult[0xb] = 0;
  outResult[0xc] = 0;
  outResult[0xd] = 0;
  outResult[0xe] = 0;
  outResult[0xf] = defaultVal;
  return 0;
}
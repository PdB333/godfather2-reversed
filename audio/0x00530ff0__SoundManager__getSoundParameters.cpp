// FUNC_NAME: SoundManager::getSoundParameters
void SoundManager::getSoundParameters(void)

{
  uint soundIndex;
  undefined1 *soundEntry;
  float in_XMM1_Da;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  
  if (soundIndex < 0x1000) {
    soundEntry = &DAT_011a0f28 + soundIndex * 0x38;  // Sound table at 0x011a0f28, 0x38 bytes per entry
  }
  else {
    soundEntry = (undefined1 *)0x0;
  }
  local_20 = in_XMM1_Da / (float)*(ushort *)(soundEntry + 2);  // Divide by some sound parameter from entry+2
  local_1c = in_XMM1_Da / (float)*(ushort *)(soundEntry + 4);  // Divide by some sound parameter from entry+4
  local_18 = DAT_00e44564 - local_20;  // Subtract from global constant
  local_14 = local_1c;
  if (DAT_01219954 == DAT_01219a4c) {
    FUN_0060add0(DAT_01219954,DAT_01219a28,&local_20);
    return;
  }
  if (DAT_01219954 == DAT_01219a50) {
    FUN_0060add0(DAT_01219954,DAT_01219a24,&local_20);
    return;
  }
  if (DAT_01219954 == DAT_01219a58) {
    FUN_0060add0(DAT_01219954,DAT_01219a2c,&local_20);
    return;
  }
  if ((DAT_01219954 == DAT_01219a68) && (DAT_01219a5c != 0)) {
    FUN_0060add0(DAT_01219954,DAT_01219a5c,&local_20);
  }
  return;
}
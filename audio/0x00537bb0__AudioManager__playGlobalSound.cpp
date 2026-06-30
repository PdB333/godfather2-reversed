// FUNC_NAME: AudioManager::playGlobalSound
void AudioManager::playGlobalSound(int soundId1, int soundId2) // param_1 = soundId1, param_2 = soundId2
{
  // Play ambient sound 1 through sound manager 1 (DAT_0121a394)
  FUN_0060add0(DAT_0121a394, *(undefined4 *)(DAT_0121b0a8 + 0xc)); // +0xc = first sound handle offset
  // Play ambient sound 2 with additional parameter through same manager
  FUN_0060add0(DAT_0121a394, *(undefined4 *)(DAT_0121b0a8 + 0x10), soundId2); // +0x10 = second sound handle offset
  // Play 3D positioned sound through sound manager 1, positioned at soundId1
  FUN_0060aa90(DAT_0121a394, *(undefined4 *)(DAT_0121b0a8 + 8), soundId1); // +0x08 = 3D sound handle offset
  // Check for alternative audio setup (DAT_0121b638)
  if (DAT_0121b638 != 0) {
    // Play through secondary audio system (possibly music/voice channel)
    FUN_0060add0(DAT_0121a390, *(undefined4 *)(DAT_0121b638 + 0x1c)); // +0x1c = secondary sound handle offset
    return;
  }
  // Default fallback through tertiary audio system
  FUN_0060add0(DAT_0121a390, *(undefined4 *)(DAT_0121b63c + 0x14)); // +0x14 = fallback sound handle offset
}
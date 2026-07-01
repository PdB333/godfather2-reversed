// FUNC_NAME: AudioManager::playSample
void AudioManager::playSample(int sampleIndex, undefined4 param_2)
{
  // DAT_00d83070 is likely an array of audio sample pointers (e.g., sampleHandles)
  // param_1 is the index into this array
  if (*(int *)(&DAT_00d83070 + sampleIndex * 4) != 0) {
    // 0x4d504750 = 'MPGP' (likely a magic identifier for audio playback)
    // FUN_009085c0 is probably the internal audio playback function
    FUN_009085c0(0x4d504750, *(int *)(&DAT_00d83070 + sampleIndex * 4), param_2);
  }
}
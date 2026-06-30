// FUNC_NAME: AudioManager::playSoundUI
void AudioManager::playSoundUI(void)
{
  // 0x0119caf0 is probably the AudioManager singleton or a function pointer table
  // Call to a registered function pointer with first arg 8 (likely a sound ID or channel) and second arg 0 (probably flags/volume/priority)
  (*DAT_0119caf0)(8, 0);
  return;
}
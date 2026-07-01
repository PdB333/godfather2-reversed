// FUNC_NAME: AudioManager::playSoundEffect
void AudioManager::playSoundEffect(void)
{
  // Save current audio state
  undefined4 savedState = DAT_00e54a0c;  // Global audio state variable
  
  // Play sound effect with ID 0x320036a1
  AudioManager::playSound(0x320036a1);
  
  // Set audio callback/event handler
  AudioManager::setAudioCallback(&LAB_0090d6a0);
  
  // Restore previous audio state
  DAT_00e54a0c = savedState;
  
  // Process audio state change
  AudioManager::processAudioStateChange(savedState);
  
  return;
}
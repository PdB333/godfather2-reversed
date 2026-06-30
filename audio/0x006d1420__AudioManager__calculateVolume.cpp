// FUNC_NAME: AudioManager::calculateVolume
float __thiscall AudioManager::calculateVolume(void* this, bool isMusic, float inputVolume)
{
  char isMuted;
  float clampedVolume;
  float result;
  
  isMuted = FUN_00410eb0(this);  // Check if audio is muted
  if (isMuted != '\0') {
    return (float)_DAT_00e510e8 * (float)inputVolume;  // Return master volume * input
  }
  
  clampedVolume = DAT_00d5ccf8;  // Minimum volume threshold
  if ((DAT_00d5ccf8 <= inputVolume) && (clampedVolume = _DAT_00d5780c, inputVolume <= _DAT_00d5780c)) {
    clampedVolume = inputVolume;  // Clamp between min and max
  }
  
  // Apply volume curve using bitwise AND with mask
  result = (float)(float)((uint)clampedVolume & DAT_00e44680);
  
  if (isMusic != '\0') {
    // Music volume curve: lerp between music min and max using result
    return ((float)1 - result) * (float)_DAT_00e510ec + (float)_DAT_00e510f0 * result;
  }
  
  // SFX volume curve: lerp between SFX min and max using result
  return ((float)1 - result) * (float)_DAT_00e510e4 + (float)_DAT_00e510e8 * result;
}
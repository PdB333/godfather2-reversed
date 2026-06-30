// FUNC_NAME: SoundManager::updateActiveSoundData
void __thiscall SoundManager::updateActiveSoundData(void)
{
  // Check if active sound handle exists (offset +0x98 typically a pointer or handle)
  if (*(int *)(this + 0x98) != 0) {
    // Retrieve sound position/source info from the audio system
    void *soundInfo = (void *)FUN_0061f770(*(void **)(this + 0x9c));
    if (soundInfo != (void *)0x0) {
      // Copy 3 floats (position) from the sound info object
      _DAT_012059d0 = *(float *)(soundInfo + 0x30); // x
      _DAT_012059d4 = *(float *)(soundInfo + 0x34); // y
      _DAT_012059d8 = *(float *)(soundInfo + 0x38); // z
      // Flag whether the current sound is active (from this object's byte at +0x8D)
      DAT_01205887 = *(byte *)(this + 0x8d);
      return;
    }
    // If no valid sound info, zero out the global position and flag
    _DAT_012059d8 = 0.0f;
    _DAT_012059d4 = 0.0f;
    _DAT_012059d0 = 0.0f;
    DAT_01205887 = 0;
  }
  return;
}
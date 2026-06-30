// FUNC_NAME: AudioDataManager::releaseSoundSlot
void AudioDataManager::releaseSoundSlot(void)
{
  // +0x26c: m_pActiveVoice (voice pointer)
  // +0x281: m_bVoiceActive (flag)
  // +0x282: m_bVoiceFinished (flag)
  // +0x27c: m_voiceId (sound identifier)
  if ((*(this + 0x26c) != 0) && (*(this + 0x281) != 0) && (*(this + 0x282) == 0)) {
    // If voice is active and not finished, stop it with category 7
    // g_pAudioDataManager is global singleton at 0x0122350c
    FUN_005e25a0(DAT_0122350c, *(this + 0x27c), 7);
  }

  // Reset timers or counters at +0x1b4 and +0x1b8
  *(this + 0x1b4) = 0;
  *(this + 0x1b8) = 0;

  // Release reference-counted pointer at +0x484
  if (*(this + 0x484) != 0) {
    int pRefCounted = *(this + 0x484);
    *(this + 0x484) = 0;
    // FUNCTION_005e8900 returns true if reference was successfully removed
    if (FUN_005e8900() != 0) {
      // Update previous pointer at +0x480
      *(this + 0x480) = pRefCounted;
    }
  }

  // Save and invalidate handles at +0x1cc and +0x1d0
  int savedHandle = *(this + 0x1cc);
  *(this + 0x1cc) = -1;
  *(this + 0x1d0) = -1;
  *(this + 0x1d8) = 0;
  *(this + 0x1dc) = 0;

  // If slot index at +0x1c8 is valid (non-negative), release it
  if (*(this + 0x1c8) >= 0) {
    // +0x1ec: some flag to reset
    *(this + 0x1ec) = 0;

    // g_pResourceManager is global at 0x01223510
    // Vtable calls: release slot, release resource handle, destroy handle
    // offset 0x6c: void releaseSlot(int slotId, int zero)
    (**(code **)(*DAT_01223510 + 0x6c))(*(this + 0x1c8), 0);
    // offset 0x9c: void releaseResource(int handle, int delayMs = 50)
    (**(code **)(*DAT_01223510 + 0x9c))(savedHandle, 0x32);
    // offset 0xa0: void destroyHandle(int slotId)
    (**(code **)(*DAT_01223510 + 0xa0))(*(this + 0x1c8));
    // End-of-function cleanup
    FUN_005dbc10();
  }
  return;
}
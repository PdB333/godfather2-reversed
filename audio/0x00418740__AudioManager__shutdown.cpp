// FUNC_NAME: AudioManager::shutdown
void __thiscall AudioManager::shutdown(AudioManager *this)
{
  int soundEngine;
  bool bEnginePresent;
  
  soundEngine = g_soundEngine;
  bEnginePresent = g_soundEngine != 0;
  this->vtable = &s_SoundEngineVTable; // +0x0: initial vtable
  if (bEnginePresent) {
    releaseSoundEngine(soundEngine);
    g_soundEngine = 0;
  }
  if (g_audioStream != 0) {
    releaseAudioStream(g_audioStream);
    g_audioStream = 0;
  }
  this->vtable = &s_ShutdownVTable; // +0x0: set to shutdown vtable after cleanup
  return;
}
// FUNC_NAME: shutdownAudioSystem
void shutdownAudioSystem(void)

{
  undefined4 audioManager;
  
  audioManager = getAudioDataManager();
  releaseAudioDataManager(audioManager);
  audioManager = getBNKStreamManager();
  releaseBNKStreamManager(audioManager);
  if (DAT_0112f970 != (undefined4 *)0x0) {
    (**(code **)*DAT_0112f970)(1); // Release audio playback object
  }
  DAT_0112f970 = (undefined4 *)0x0;
  if (DAT_0112f974 != (undefined4 *)0x0) {
    (**(code **)*DAT_0112f974)(1); // Release audio stream object
  }
  DAT_0112f974 = (undefined4 *)0x0;
  return;
}
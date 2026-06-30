// FUNC_NAME: cleanupAudioStreams
void cleanupAudioStreams(void)
{
  if (*DAT_0121b0a8 != 0) {
    FUN_006063b0(); // likely AudioDataManager or BNKStreamManager::releaseStream
  }
  if (DAT_0121b0a8[1] != 0) {
    FUN_006063b0();
  }
  return;
}
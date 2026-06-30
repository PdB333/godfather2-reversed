// FUNC_NAME: AudioDataManager::updateStreams
void AudioDataManager::updateStreams(void)
{
  undefined4 streamHandle;
  
  streamHandle = AudioDataManager::getNextPendingStream();
  AudioDataManager::processStream(streamHandle);
  return;
}
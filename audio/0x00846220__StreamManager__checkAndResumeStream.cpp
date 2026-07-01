// FUNC_NAME: StreamManager::checkAndResumeStream
void __fastcall StreamManager::checkAndResumeStream(int this) // +0x144 = stream handle
{
  char isPlaying;
  
  isPlaying = FUN_004b1730(*(undefined4 *)(this + 0x144)); // BNKStreamManager::isStreamPlaying(streamHandle)
  if (isPlaying == '\0') {
    FUN_004b1880(*(undefined4 *)(this + 0x144)); // BNKStreamManager::resumeStream(streamHandle)
  }
  return;
}
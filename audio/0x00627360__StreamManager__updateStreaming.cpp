// FUNC_NAME: StreamManager::updateStreaming
void StreamManager::updateStreaming(void)
{
  // Save current streaming state
  uint savedState = StreamManager::saveStreamingState(); // FUN_00627290
  
  // Pause streaming
  StreamManager::pauseStreaming(); // FUN_00626f80
  
  // Set streaming priority to 0 (lowest)
  StreamManager::setStreamingPriority(0); // FUN_00626fd0
  
  // Pause streaming again (likely to ensure state)
  StreamManager::pauseStreaming(); // FUN_00626f80
  
  // Restore streaming state
  StreamManager::restoreStreamingState(savedState); // FUN_00627010
  
  // Resume streaming
  StreamManager::resumeStreaming(); // FUN_006270e0
  
  return;
}
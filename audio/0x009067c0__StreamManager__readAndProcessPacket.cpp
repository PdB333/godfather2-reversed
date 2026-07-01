// FUNC_NAME: StreamManager::readAndProcessPacket
void __thiscall StreamManager::readAndProcessPacket(int param_1,undefined4 param_2)
{
  int *streamBuffer;
  char isPaused;
  int result;
  undefined4 dataChunk;
  
  // Initialize stream reader with the input data
  FUN_009065c0(param_2);
  // Setup decoder with specific key/seed (0x70c99030)
  FUN_0043aff0(param_2,0x70c99030);
  
  // Main loop: continue reading while stream is not paused
  isPaused = FUN_0043b120();
  while (isPaused == '\0') {
    // Advance to next chunk boundary
    FUN_0043b210();
    result = FUN_0043ab70();
    if (result == 0) {
      // No error - read a data chunk
      FUN_0043b210();
      dataChunk = FUN_0043ab90();
      streamBuffer = (int *)(param_1 + 0x68);  // +0x68: pointer to stream data buffer
      FUN_00408980(streamBuffer,dataChunk);     // Copy data into buffer
      if (*streamBuffer != 0) {
        // Process the streamed data (0x8000 = 32KB buffer size)
        FUN_00408900(param_1 + 0x3c,streamBuffer,0x8000);  // +0x3c: stream context/state
      }
    }
    // Sync after chunk processing
    FUN_0043b1a0();
    isPaused = FUN_0043b120();
  }
  return;
}
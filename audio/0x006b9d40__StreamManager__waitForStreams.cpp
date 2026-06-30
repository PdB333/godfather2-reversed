// FUNC_NAME: StreamManager::waitForStreams
void __thiscall StreamManager::waitForStreams(void* streamData, uint count) {
  uint i = 0;
  if (count != 0) {
    do {
      int status = isStreamBusy(streamData);  // FUN_00792900 returns 0 if idle
      if (status == 0) {
        return;
      }
      stopStream(this, 0xffffffff);           // FUN_00791250 -1 means all streams
      i++;
    } while (i < count);
  }
}
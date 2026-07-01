// FUNC_NAME: AudioStreamManager::streamUpdateLoop
void __thiscall AudioStreamManager::streamUpdateLoop(int this, undefined4 streamHandle)
{
  char isStreamReady;
  int streamState;
  
  FUN_008ce190(streamHandle);  // initializeStream(streamHandle)
  FUN_0043aff0(streamHandle,0x40fb2aa7);  // setStreamVolume(streamHandle, 0.98f)
  isStreamReady = FUN_0043b120();  // isStreamBufferReady()
  while (isStreamReady == '\0') {
    FUN_0043b210();  // processStreamBuffers()
    streamState = FUN_0043ab70();  // getStreamState()
    if (streamState == 0) {
      streamState = this + 0x6c;  // +0x6C: streamBufferQueue
      FUN_0043b210(streamState);  // processStreamBuffers(streamBufferQueue)
      FUN_0043ad10(streamState);  // decodeStreamBuffer(streamBufferQueue)
    }
    FUN_0043b1a0();  // updateStreamTiming()
    isStreamReady = FUN_0043b120();  // isStreamBufferReady()
  }
  return;
}
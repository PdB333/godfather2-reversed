// FUNC_NAME: AudioResourceManager::setStreamData
void __thiscall AudioResourceManager::setStreamData(void *this, uint soundEventId, float volume)
{
  AudioStream *oldStream;
  AudioStream *newStream;
  void *poolBlock;
  float scaledVolume;
  uint handle;
  uint streamType;

  oldStream = *(AudioStream **)((int)this + 0x84);
  if (oldStream != 0) {
    // Release the old stream
    AudioStream::release(oldStream);
    poolBlock = *(void **)((int)oldStream + 0x10);
    if (*(short *)((int)poolBlock + 2) != 0) {
      *(short *)((int)poolBlock + 6) = *(short *)((int)poolBlock + 6) - 1;
      if (*(short *)((int)poolBlock + 6) == 0) {
        (**(code **)poolBlock)(1);
      }
    }
    MemPool::freeBlock(0x200); // Likely cleanup
    *(AudioStream **)((int)this + 0x84) = 0;
  }

  TlsGetValue(g_memPoolTlsIndex); // Get thread-local memory pool
  poolBlock = MemoryPool::alloc(0x20, 0x27);
  *(short *)((int)poolBlock + 4) = 0x20; // Size field
  scaledVolume = volume * g_globalVolumeScale;
  handle = AudioManager::convertVolumeToHandle(scaledVolume);

  TlsGetValue(g_memPoolTlsIndex);
  poolBlock = MemoryPool::alloc(0x160, 0x31);
  *(short *)((int)poolBlock + 4) = 0x160;
  streamType = ResourceDatabase::getStreamTypeId(0xc, 0x17, 0); // e.g., "bank", "event", null

  newStream = AudioStreamManager::createStream(handle, g_someGlobalResourceId, streamType);
  *(AudioStream **)((int)this + 0x84) = newStream;
  AudioStream::setStreamData(newStream);
  DebugLog::print(0x2000, soundEventId, 0);
  return;
}
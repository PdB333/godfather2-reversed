// FUNC_NAME: StreamBufferManager::StreamBufferManager
StreamBufferManager * __thiscall StreamBufferManager::StreamBufferManager(StreamBufferManager *this, int arg)
{
  unsigned int handle;
  int allocResult;
  StreamBuffer *subObject;
  bool isEnabled;
  unsigned char dummyFlag;
  int loopCount;

  isEnabled = gEnableStreaming != 0;
  gStreamBufferManager = this;
  this->vtable = &StreamBufferManager_VTable;
  if (isEnabled) {
    EnterCriticalSection();
    // Load a resource identified by hash 0xfab591a1 (likely streaming buffer)
    handle = ResourceManager::LoadResource(0xfab591a1, 2, *(int *)(arg + 0x14), 5, gEnableStreaming, 0, 0);
    this->resourceHandle = handle;
    LeaveCriticalSection();
    dummyFlag = 0;
    subObject = this->subObjects;
    loopCount = 2;
    do {
      allocResult = Memory::Allocate(0x218);
      if (allocResult == 0) {
        *subObject = 0;
      }
      else {
        *subObject = SubObject::Create(&dummyFlag);
      }
      subObject++;
      loopCount--;
    } while (loopCount != 0);
  }
  return this;
}
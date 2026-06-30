// FUNC_NAME: StreamManager::createStreamObject
void StreamManager::createStreamObject(unsigned int param_1)
{
  // Allocate 20-byte stream object
  StreamObject *pObj = (StreamObject *)operator new(0x14);
  if (pObj != (StreamObject *)0x0) {
    // +0x00: back pointer to owner (this manager)
    pObj->owner = this;
    // +0x10: stream type identifier
    pObj->type = param_1;
    // Local creation parameters: version=2, size=0x10, flags=0
    CreateParams params;
    params.version = 2;
    params.size = 0x10;
    params.flags = 0;
    // Call virtual function to allocate a handle (likely index 0 in vtable)
    unsigned int handle = this->allocateStreamHandle(param_1, &params);
    // +0x08 and +0x0C: both store the same handle (possibly for read/write)
    pObj->handle1 = handle;
    pObj->handle2 = handle;
    // +0x04: counter reset
    pObj->counter = 0;
    // Store globally as the active stream
    g_pStreamObject = pObj;
    return;
  }
  g_pStreamObject = (StreamObject *)0x0;
  return;
}
// FUNC_NAME: EventDispatcher::dispatchEvent
void __thiscall EventDispatcher::dispatchEvent(EventDispatcher* this, int eventData)
{
  int syncResult[3];
  int asyncResult[3];
  void (*asyncCallback)(int) = nullptr;
  void (*syncCallback)(int) = nullptr;
  
  this->lock();
  if (EventDispatcher::isAsyncMode() == 0) {
    if (g_asyncEventPoolIndex < 0) {
      return;
    }
    if (g_eventPoolEnd - g_eventPoolStart >> 2 <= g_asyncEventPoolIndex) {
      return;
    }
    this->lock();
    EventDispatcher::createSyncResult(syncResult, eventData); // fills syncResult[0] with pointer, syncResult[1] with callback?
  }
  else {
    this->lock();
    int asyncResultHandle = EventDispatcher::createAsyncResult(asyncResult, eventData);
    EventDispatcher::destroySyncResult(syncResult); // clear sync buffer
    this->release(asyncResultHandle);
    if (asyncResult[0] != 0) {
      asyncCallback(asyncResult[0]); // call async completion callback
    }
  }
  if (syncResult[0] != 0) {
    syncCallback(syncResult[0]); // call sync completion callback
  }
}
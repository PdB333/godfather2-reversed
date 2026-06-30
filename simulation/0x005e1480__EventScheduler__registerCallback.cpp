// FUNC_NAME: EventScheduler::registerCallback
void EventScheduler::registerCallback(ICallback *callback, int eventId)
{
  // Store callback pointer at this+0x4
  this->callback = callback;

  // Call callback's virtual method at vtable offset 0x8 (e.g., onRegister)
  callback->onRegister();

  if (eventId != 0) {
    // Lookup or validate eventId, store result at this+0x8
    this->eventHandle = FUN_004265d0(eventId, this->callback);
    // Call callback's virtual method at vtable offset 0x4 (e.g., setEventId) with (eventId, 0)
    callback->setEventId(eventId, 0);
    // Call callback's virtual method at vtable offset 0xc (e.g., onFinalize)
    callback->onFinalize();
    return;
  }
  // If eventId is zero, clear handle and still call finalize
  this->eventHandle = 0;
  callback->onFinalize();
}
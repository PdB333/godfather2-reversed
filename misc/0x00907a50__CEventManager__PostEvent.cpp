// FUNC_NAME: CEventManager::PostEvent

void __thiscall CEventManager::PostEvent(CEventManager* this, uint eventType, uint extraData)
{
  CEvent* event;
  
  // eventType must be < 29 (max supported event types)
  if (eventType < 0x1d) {
    event = (CEvent*)FUN_009c8e80(0x14); // allocate 20 bytes for CEvent
    if (event != (CEvent*)0x0) {
      // constructor call via vector_constructor_iterator (single element)
      _vector_constructor_iterator_(event, 0x14, 1, (_func_void_ptr_void_ptr *)&LAB_00907620);
    } else {
      event = (CEvent*)0x0;
    }
    // +0x08: store the event callback/data from the table
    event->callbackData = *(undefined4*)(*(int*)(this + 4) + eventType * 4);
    // +0x10: unknown field, set to 0
    event->field_10 = 0;
    // +0x00: event type identifier (3 = some specific type)
    event->type = 3;
    // +0x0C: user-supplied extra data
    event->extraData = extraData;
    // push the event onto the processing queue (parameters: event, 1, callback, 0)
    FUN_00566000(event, 1, &LAB_00907660, 0);
  }
  return;
}
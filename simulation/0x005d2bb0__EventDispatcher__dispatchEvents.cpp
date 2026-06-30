// FUNC_NAME: EventDispatcher::dispatchEvents
void EventDispatcher::dispatchEvents(void)
{
  undefined8 eventData;
  int eventType;
  int *listenerEntry;
  int listenerIndex;
  code *handlerFunc;
  int *listenerArray;
  undefined4 eventDataLow;
  int eventDataHigh;
  
  int remainingEvents = *(int *)(this + 0x54); // +0x54: remaining event count
  do {
    if (remainingEvents == 0) {
      return;
    }
    int currentIndex = *(int *)(this + 0x50); // +0x50: current event index
    eventData = *(undefined8 *)(*(int *)(this + 0x48) + currentIndex * 0xc); // +0x48: event queue array
    eventType = *(int *)(*(int *)(this + 0x48) + currentIndex * 0xc + 8); // event type at offset +8
    *(int *)(this + 0x50) = currentIndex + 1;
    if (*(int *)(this + 0x4c) <= currentIndex + 1) { // +0x4c: queue capacity
      *(undefined4 *)(this + 0x50) = 0;
    }
    *(int *)(this + 0x54) = *(int *)(this + 0x54) + -1;
    eventDataHigh = (int)((ulonglong)eventData >> 0x20);
    if (((eventDataHigh != -1) && (*(char *)(this + 0x58) != '\0')) && // +0x58: enabled flag
       (listenerIndex = *(int *)(this + 0x44) + -1, -1 < listenerIndex)) { // +0x44: listener count
      eventDataLow = (undefined4)eventData;
      listenerArray = (int *)(this + 4 + listenerIndex * 4); // +0x04: listener array
      do {
        listenerEntry = (int *)*listenerArray;
        // Check if listener matches event ID (low and high parts)
        if (((listenerEntry[3] & 1 << ((byte)eventData & 0x1f)) != 0) &&
           ((listenerEntry[2] & 1 << ((byte)((ulonglong)eventData >> 0x20) & 0x1f)) != 0)) {
          if (listenerEntry[5] != 0) break; // +0x14: some flag, skip if set
          if (eventType == 0) {
            handlerFunc = *(code **)(*listenerEntry + 4); // vtable+4: handler for type 0
          }
          else if (eventType == 1) {
            handlerFunc = *(code **)(*listenerEntry + 8); // vtable+8: handler for type 1
          }
          else {
            if (eventType != 2) break;
            handlerFunc = *(code **)(*listenerEntry + 0xc); // vtable+0xc: handler for type 2
          }
          (*handlerFunc)(eventDataLow, eventDataHigh);
          break;
        }
        listenerIndex = listenerIndex + -1;
        listenerArray = listenerArray + -1;
      } while (-1 < listenerIndex);
    }
    remainingEvents = *(int *)(this + 0x54);
  } while( true );
}
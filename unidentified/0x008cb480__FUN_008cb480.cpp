// FUNC_NAME: SomeClass::addTimedEvent
void __thiscall addTimedEvent(int this, int eventId, int eventData)
{
  uint count;
  
  count = *(uint *)(this + 0x1f50); // +0x1f50: eventCount (number of stored timed events)
  if (count < 500) {
    *(int *)(this + 0xfb0 + count * 8) = eventId;      // +0xfb0: eventId array (500 entries, 8 bytes each)
    *(int *)(this + 0xfb4 + count * 8) = eventData;    // +0xfb4: eventData array (paired with eventId)
    *(int *)(this + 0x1f50) = count + 1;               // Increment event count
  }
  return;
}
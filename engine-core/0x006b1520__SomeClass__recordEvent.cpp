// FUNC_NAME: SomeClass::recordEvent
void __thiscall SomeClass::recordEvent(int this, int eventData)
{
  uint eventType;
  int *counterPtr;
  
  // eventData is the original pointer, but we use the value at +0x38 as a key for lookup
  int key = *(int *)(eventData + 0x38); // +0x38: event type or category
  counterPtr = (int *)FUN_006b1280(&key); // lookup or create counter for this key
  *counterPtr = eventData; // store the event data pointer in the counter slot
  
  eventType = *(uint *)(eventData + 0xc4); // +0xc4: event type index (0-9)
  if (eventType < 10) {
    // Increment per-type counter stored in this+0x40 array of 10 ints
    counterPtr = (int *)(this + 0x40 + eventType * 4); // +0x40: array of 10 event type counters
    *counterPtr = *counterPtr + 1;
  }
  return;
}
// FUNC_NAME: OnlineEventManager::handleOnlineEvent
void __thiscall handleOnlineEvent(int this, undefined4 *eventData, int isImportant, undefined4 eventId, undefined4 eventValue)
{
  undefined1 *eventName;
  undefined *prefix;
  undefined1 *formattedString [3];
  code *deallocator;
  
  eventName = (undefined1 *)*eventData;
  if (eventName == (undefined1 *)0x0) {
    eventName = &DAT_0120546e; // Default empty string
  }
  prefix = &DAT_00e35154; // "[c=white]"
  if (isImportant != 0) {
    prefix = &DAT_00e35114; // "[c=yellow]"
  }
  // Format: "[c=%s]%s[c=RESET] [b=OnlineEvent%u] %u"
  FUN_004d4a60(formattedString, 1, "[c=%s]%s[c=RESET] [b=OnlineEvent%u] %u", prefix, eventName, eventId, eventValue);
  
  eventName = formattedString[0];
  if (formattedString[0] == (undefined1 *)0x0) {
    eventName = &DAT_0120546e;
  }
  // Log the event
  FUN_005a04a0("InformEvent", 0, &DAT_00d8b7d4, 1, eventName);
  
  // Clear pending event flag at +0x50
  *(undefined4 *)(this + 0x50) = 0;
  
  // Show ticker
  FUN_005a04a0("ShowTicker", 0, &DAT_00d8b7d4, 0);
  
  // Start timer for next event check (callback at 0x0094e300)
  FUN_005c0260(this + 0x10, &LAB_0094e300, 1);
  
  // Free formatted string if allocated
  if (formattedString[0] != (undefined1 *)0x0) {
    (*deallocator)(formattedString[0]);
  }
  return;
}
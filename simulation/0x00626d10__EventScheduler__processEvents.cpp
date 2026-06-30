// FUNC_NAME: EventScheduler::processEvents
void EventScheduler::processEvents(int *eventListHead)
{
  int *currentEvent;
  
  currentEvent = (int *)*eventListHead;
  while (currentEvent != (int *)0x0) {
    currentEvent = (int *)*eventListHead;
    switch(*(undefined1 *)((int)currentEvent + 4)) {
    case 5: // kEventType_5 - likely a timer or delayed action
      *eventListHead = *(int *)((int)currentEvent + 0x18);
      FUN_006267a0(eventListHead,currentEvent);
      break;
    case 6: // kEventType_6 - likely a sound or audio event
      *eventListHead = *(int *)((int)currentEvent + 8);
      FUN_006269b0();
      break;
    case 8: // kEventType_8 - likely a mission or objective event
      *eventListHead = *(int *)((int)currentEvent + 0x4c);
      FUN_00626ac0();
      break;
    case 9: // kEventType_9 - likely a dialog or cutscene event
      *eventListHead = *(int *)((int)currentEvent + 0x40);
      FUN_00626910();
    }
    currentEvent = (int *)*eventListHead;
  }
  return;
}
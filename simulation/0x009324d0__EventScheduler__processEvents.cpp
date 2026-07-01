// FUNC_NAME: EventScheduler::processEvents
void EventScheduler::processEvents(void)
{
  char bResult;
  
  bResult = isTimerExpired((Timer*)0x01206978);
  if (bResult != '\0') {
    resetTimer((Timer*)0x01206978);
  }
  processQueuedEvents();
  return;
}
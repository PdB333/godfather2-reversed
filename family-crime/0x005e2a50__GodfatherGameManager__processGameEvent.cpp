// FUNC_NAME: GodfatherGameManager::processGameEvent
void GodfatherGameManager::processGameEvent(int eventType, int eventData1, int eventData2)
{
  // Check if game event processing is enabled (flag at +0x1744)
  if (*(char *)(DAT_0122350c + 0x1744) != '\0') {
    // Delegate to the actual event handler function with default timeout
    this->emitGameEvent(eventType, eventData1, eventData2, -1);
  }
  return;
}
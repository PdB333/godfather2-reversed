// FUNC_NAME: EventManager::toggleEvent
void __thiscall EventManager::toggleEvent(int this, char toggleFlag)
{
  bool isPresent = false;
  int i = 0;
  int *idList;           // +0x74: array of event/feature IDs
  int idCount;           // +0x78: number of entries in idList
  char logBuffer[12];    // used only for debug string conversion

  idCount = *(int *)(this + 0x78);
  if (0 < idCount) {
    idList = *(int **)(this + 0x74);
    do {
      if (*idList == 0x2004) {
        isPresent = true;
        break;
      }
      i = i + 1;
      idList = idList + 1;  // each entry is 4 bytes
    } while (i < idCount);
  }

  // If toggleFlag is 0, only log the event ID if it is already active
  if (toggleFlag == '\0') {
    if (isPresent) {
      FUN_009f0250(logBuffer, 0x2004);  // debug: convert ID to string
    }
    return;
  }

  // toggleFlag != 0: toggle the state of event 0x2004
  if (!isPresent) {
    FUN_009f01f0(0x2004, 1, 0);  // add/enable event
  } else {
    FUN_009f0300(0x2004, 1, 0);  // remove/disable event
  }
}
// FUNC_NAME: DebugLogManager::pushEntryAndPrintPrevious
void DebugLogManager::pushEntryAndPrintPrevious(void)
{
  LogEntry *newEntry;
  LogEntry *topEntry;
  int currentPointer;
  LogEntry *prevEntry;
  char *stringPtr;
  FILE *logFile;

  acquireMutex();                                 // FUN_00625ca0 - log mutex lock
  newEntry = getNewLogEntry();                    // FUN_00633cb0 - returns pointer to 8-byte entry data
  currentPointer = *(int *)(this + 0x08);         // +0x08: current stack top pointer
  *(undefined4 *)(currentPointer + -8) = newEntry->data1; // write first dword at offset -8 from top
  *(undefined4 *)(currentPointer + -4) = newEntry->data2; // write second dword at offset -4
  topEntry = *(LogEntry **)(this + 0x08);         // reload top pointer (still before decrement)
  // Check if there is a previous entry and its type is 6
  if ((topEntry - 2 != NULL) && ((topEntry - 2)->type == 6)) {
    // Shift all entries up to make room (pop one and overwrite)
    for (prevEntry = topEntry; topEntry - 4 < prevEntry; prevEntry = prevEntry - 2) {
      prevEntry->data1 = (prevEntry - 2)->data1;
      prevEntry->data2 = (prevEntry - 2)->data2;
    }
    // Move the first entry (top of stack) into the vacated slot
    topEntry = *(LogEntry **)(this + 0x08);       // reload after shift
    (topEntry - 2)->data1 = topEntry->data1;       // copy first element's data
    (topEntry - 2)->data2 = topEntry->data2;
    handleSpecialType();                           // FUN_006362d0 - process type 6
    return;
  }
  // Normal case: process previous entry (two below the newly pushed one)
  prevEntry = topEntry - 4;                        // point to entry two slots below top
  if (prevEntry != NULL) {
    if (prevEntry->type == 4) {
      stringPtr = (char *)(prevEntry->data2 + 0x10); // +0x10: string field offset for type 4
    }
    else {
      if (checkCondition() != 0) {                 // FUN_00633990
        stringPtr = (char *)(prevEntry->data2 + 0x10);
      }
      else {
        stringPtr = NULL;
      }
      // Check if the log buffer is full and needs flushing
      if (*(uint *)(*(int *)(this + 0x10) + 0x20) <=
          *(uint *)(*(int *)(this + 0x10) + 0x24)) {
        flushLogBuffer();                          // FUN_00627360
      }
    }
  }
  // Print the string from the previous entry
  logFile = (FILE *)(getLogFile(&s_logFormatString, stringPtr) + 0x40); // FUN_00b995f7 - returns file handle? +0x40 offset
  fprintf(logFile, "%s\n", stringPtr);
  // Pop the top entry (the one we just pushed is not printed; the previous one is printed and removed)
  *(int *)(this + 0x08) = *(int *)(this + 0x08) - 0x10; // decrement stack pointer by one entry (16 bytes)
  return;
}
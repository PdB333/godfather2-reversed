// FUNC_NAME: Player::formatTimeString
void __thiscall Player::formatTimeString(int this, char* outBuffer)
{
  char* timeStr;
  int timeVal;
  int minutes;
  int seconds;
  char* fallbackStr;
  
  timeStr = (char *)0x0;
  minutes = 0;
  seconds = 0;
  fallbackStr = (char *)0x0;
  
  // Get time value from player data at offset +0x24 (likely game time or mission time)
  timeVal = *(int *)(this + 0x24);
  
  // Convert to minutes:seconds format (modulo 60 for seconds)
  FUN_006042f0((uint)timeVal % 0x3c, 0, &timeStr);
  
  // If conversion failed, use empty string
  if (timeStr == (char *)0x0) {
    timeStr = &DAT_0120546e;  // Empty string constant
  }
  
  // Copy formatted time string to output buffer (max 0x80 chars)
  FUN_005c4660(outBuffer, timeStr, 0x80, seconds);
  
  // Free allocated string if needed
  if (timeStr != (char *)0x0) {
    (*fallbackStr)(timeStr);  // Likely operator delete or free
  }
  
  return;
}
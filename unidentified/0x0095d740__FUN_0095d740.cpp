// FUNC_NAME: SomeClass::formatTimeAndCopyStrings
void __thiscall formatTimeAndCopyStrings(int this, undefined4 param2, undefined4 param3, undefined4 param4, undefined4 param5, undefined4 param6)
{
  uint totalSeconds;
  undefined1 *timeString;
  undefined4 local_c;
  undefined4 local_8;
  code *local_4;
  
  totalSeconds = *(uint *)(this + 0x28); // +0x28: total seconds (e.g., game time)
  timeString = (undefined1 *)0x0;
  local_c = 0;
  local_8 = 0;
  local_4 = (code *)0x0;
  // Convert total seconds to hours, minutes, seconds format
  FUN_00604250(totalSeconds / 0xe10, (int)(((ulonglong)totalSeconds / 0x3c) % 0x3c), totalSeconds % 0x3c, &timeString);
  // Get string from some resource/table at offset +0x20
  FUN_00603d30(*(undefined4 *)(this + 0x20), &timeString, 1);
  // Copy string to param2, using default if null
  if (timeString == (undefined1 *)0x0) {
    timeString = &DAT_0120546e; // Default empty string
  }
  FUN_005c4660(param2, timeString, param6, local_c);
  // Get string from offset +0x14
  FUN_00604000(*(undefined4 *)(this + 0x14), &timeString, 1);
  if (timeString == (undefined1 *)0x0) {
    timeString = &DAT_0120546e;
  }
  FUN_005c4660(param3, timeString, param6, local_c);
  // Get string from offset +0x24
  FUN_00603d30(*(undefined4 *)(this + 0x24), &timeString, 1);
  if (timeString == (undefined1 *)0x0) {
    timeString = &DAT_0120546e;
  }
  FUN_005c4660(param4, timeString, param6, local_c);
  // Last string from param5 (no retrieval)
  if (timeString == (undefined1 *)0x0) {
    timeString = &DAT_0120546e;
  }
  FUN_005c4660(param5, timeString, param6, local_c);
  // Free allocated string if any
  if (timeString != (undefined1 *)0x0) {
    (*local_4)(timeString);
  }
  return;
}
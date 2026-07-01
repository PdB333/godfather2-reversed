// FUNC_NAME: formatTimeToString
void __thiscall formatTimeToString(int this, undefined4 param_2, undefined4 param_3)
{
  uint totalSeconds;
  undefined1 *timeString;
  undefined4 local_c;
  undefined4 local_8;
  code *local_4;
  
  totalSeconds = *(uint *)(this + 0x1c); // +0x1c: total seconds stored in object
  timeString = (undefined1 *)0x0;
  local_c = 0;
  local_8 = 0;
  local_4 = (code *)0x0;
  // Convert total seconds to hours, minutes, seconds format
  // 0xe10 = 3600 seconds per hour, 0x3c = 60
  FUN_00604250(totalSeconds / 0xe10, (int)(((ulonglong)totalSeconds / 0x3c) % 0x3c), totalSeconds % 0x3c, &timeString);
  puVar2 = timeString;
  if (timeString == (undefined1 *)0x0) {
    puVar2 = &DAT_0120546e; // Default empty string if conversion failed
  }
  FUN_005c4660(param_2, puVar2, param_3, local_c); // Copy formatted string to output buffer
  if (timeString != (undefined1 *)0x0) {
    (*local_4)(timeString); // Free allocated string if not null
  }
  return;
}
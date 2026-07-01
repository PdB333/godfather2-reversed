// Xbox PDB: EARS_Apt_UIHudMultiplayer_OnOvertimeStart
// FUNC_NAME: TimerObjective::setTimerVisible
void __thiscall TimerObjective::setTimerVisible(char show)
{
  // +0x48: activation flag, if false, early out
  if (*(char *)(this + 0x48) != '\0') {
    // +0xb8: timer visible flag, set directly
    *(char *)(this + 0xb8) = show;
    if (show != '\0') {
      // +0xb9: overtime flag
      if (*(char *)(this + 0xb9) != '\0') {
        // +0xa8: pointer to timer format string (e.g., "Timer: %s")
        char *formatStr = *(char **)(this + 0xa8);
        if (formatStr == (char *)0x0) {
          formatStr = (char *)&DAT_0120546e; // default empty string
        }
        // FUN_005a04a0: likely a script call (e.g., "ShowTimer(format, bool)")
        FUN_005a04a0("ShowTimer", 0, &DAT_00d8b7d4, 1, formatStr);
        FUN_005a04a0("InformOvertime", 0, &DAT_00d8b7d4, 0);
        return;
      }
      
      // No overtime, show timer with different string
      char *formatStr = *(char **)(this + 0x98); // +0x98: another string pointer
      if (formatStr == (char *)0x0) {
        formatStr = (char *)&DAT_0120546e;
      }
      FUN_005a04a0("ShowTimer", 0, &DAT_00d8b7d4, 1, formatStr);
      return;
    }
    
    // Hide timer
    FUN_005a04a0("HideTimer", 0, &DAT_00d8b7d4, 0);
  }
}
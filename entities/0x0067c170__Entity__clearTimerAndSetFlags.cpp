// FUNC_NAME: Entity::clearTimerAndSetFlags
void __thiscall Entity::clearTimerAndSetFlags(uint flags)
{
  char isTimerActive;
  
  // Check if timer at +0x4C is active (non-zero and running)
  isTimerActive = Entity::isTimerActive(*(int *)(this + 0x4c));
  if (isTimerActive != '\0') {
    // Use global timer data to stop the timer
    TimerStopData stopData;
    stopData.field0 = DAT_01206840; // Global constant (e.g., timer manager or function)
    stopData.field4 = 0;
    stopData.field8 = 0;
    Entity::stopTimer(&stopData, 0);
  }
  
  // Merge flags into persistent flag field at +0x6C
  *(uint *)(this + 0x6c) |= flags;
  
  // Clear the timer pointer at +0x4C
  *(int *)(this + 0x4c) = 0;
  
  return;
}
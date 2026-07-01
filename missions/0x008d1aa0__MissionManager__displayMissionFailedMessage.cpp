// FUNC_NAME: MissionManager::displayMissionFailedMessage
void __fastcall MissionManager::displayMissionFailedMessage(int this)
{
  if (*(char *)(this + 0x1f) != '\0') {
    // +0x14: mission failed timer (float)
    // +0x1f: flag indicating mission failed message should be shown
    FUN_008d1330(this, "%.1f,Mission Failed\n", (double)*(float *)(this + 0x14));
    FUN_008d1860();
    *(undefined1 *)(this + 0x1f) = 0;
  }
  return;
}
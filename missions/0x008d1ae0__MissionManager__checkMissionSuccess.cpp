// FUNC_NAME: MissionManager::checkMissionSuccess
void __fastcall MissionManager::checkMissionSuccess(int this)
{
  if (*(char *)(this + 0x1f) != '\0') {
    // Log mission success with elapsed time (in seconds) from +0x14
    FUN_008d1330(this, "%.1f,Mission Success\n", (double)*(float *)(this + 0x14));
    FUN_008d1860(); // Likely triggers mission end/cleanup
    *(undefined1 *)(this + 0x1f) = 0; // Clear success flag
  }
  return;
}
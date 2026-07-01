// FUNC_NAME: DifficultyManager::isDifficultyAvailable
bool __thiscall DifficultyManager::isDifficultyAvailable(int this, byte difficultyIndex)
{
  bool result = true;
  // +0x50: override flag - if set, all difficulties are considered available
  if (*(int *)(this + 0x50) == 0) {
    // Get global DifficultyManager instance (or similar singleton)
    int globalDifficultyMgr = FUN_0090a5a0();
    // +0x20: byte containing the maximum difficulty index (or count)
    uint difficultyCount = FUN_008bcf60(globalDifficultyMgr + 0x20);
    // Check if the requested difficulty index (0-based) is within valid range
    result = (difficultyIndex + 1) <= (difficultyCount & 0xFF);
  }
  return result;
}
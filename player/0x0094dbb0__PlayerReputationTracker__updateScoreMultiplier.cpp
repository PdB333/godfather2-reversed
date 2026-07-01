// FUNC_NAME: PlayerReputationTracker::updateScoreMultiplier
void __thiscall PlayerReputationTracker::updateScoreMultiplier(int this, int multiplier)
{
  // +0x84: scoreMultiplier field
  *(int *)(this + 0x84) = multiplier;
  
  // Fire event "UpdateScoreMultiplier" with the multiplier value
  // FUN_005a04a0 is likely EventManager::fireEvent or similar
  FUN_005a04a0("UpdateScoreMultiplier", 0, &DAT_00d8b7d4, 0);
}
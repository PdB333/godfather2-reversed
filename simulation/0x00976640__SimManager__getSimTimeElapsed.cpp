// FUNC_NAME: SimManager::getSimTimeElapsed
int __fastcall SimManager::getSimTimeElapsed(int this)
{
  int simTime = FUN_00494d10(); // SimManager::getSimTime() - returns current simulation time
  return simTime - *(int *)(this + 0x1c); // Subtract lastUpdateTime (offset +0x1c)
}
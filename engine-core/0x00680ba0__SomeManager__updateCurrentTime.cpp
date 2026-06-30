// FUNC_NAME: SomeManager::updateCurrentTime
void SomeManager::updateCurrentTime(void)
{
  int managerPtr;
  undefined4 currentTime;
  
  managerPtr = DAT_01129878; // Global manager instance pointer
  currentTime = FUN_006808c0(DAT_01129878); // Get current time from manager
  *(undefined4 *)(managerPtr + 0x20) = currentTime; // Store time at offset +0x20
  return;
}
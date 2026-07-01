// FUNC_NAME: BuildingManager::getVenueApt3dInstance
char BuildingManager::getVenueApt3dInstance(undefined4 param_1, int param_2)
{
  char levelName [32];
  
  _sprintf(levelName, "_level%u", param_2);
  FUN_0059e490("venue_apt3d_instance", levelName);
  return ((param_2 + 1U) % 5 != 0) + '\x01';
}
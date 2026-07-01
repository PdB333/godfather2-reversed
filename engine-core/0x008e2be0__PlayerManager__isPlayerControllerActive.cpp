// FUNC_NAME: PlayerManager::isPlayerControllerActive
bool __fastcall PlayerManager::isPlayerControllerActive(int playerManager)
{
  int controllerHandle;
  
  if (playerManager == 0) {
    return false;
  }
  
  controllerHandle = FUN_0043b870(DAT_01131040); // likely InputManager::getActiveControllerHandle or XInputGetState wrapper
  
  if (controllerHandle == 0) {
    return false;
  }
  
  // Check if controller is connected and active
  // +0x1c: controller status/flags (0 = disconnected, 0x48 = connected but idle?)
  // +0x45: bit 0 = connected flag
  if (((*(int *)(controllerHandle + 0x1c) == 0) || (*(int *)(controllerHandle + 0x1c) == 0x48)) &&
     ((*(byte *)(controllerHandle + 0x45) & 1) == 0)) {
    return false;
  }
  
  return true;
}
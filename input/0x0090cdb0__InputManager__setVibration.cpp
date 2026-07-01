// FUNC_NAME: InputManager::setVibration
void __thiscall InputManager::setVibration(int this, uint controllerIndex, char enableVibration)
{
  byte controllerCount;
  char isEnabled;
  
  controllerCount = *(byte *)(DAT_01129814 + 0x14); // +0x14: activeControllerCount
  isEnabled = (char)controllerIndex;
  if (((controllerCount < 0x10) && (InputManager::setControllerEnabled(controllerCount, isEnabled == '\0'), isEnabled != '\0')) && (enableVibration != '\0')) {
    InputManager::setControllerVibration(controllerCount, 0xaf, 0xaf); // 0xaf = 175, moderate vibration
  }
  if (isEnabled == '\0') {
    *(uint *)(this + 0x14) = *(uint *)(this + 0x14) & 0xfffffffd; // +0x14: flags, clear bit 1 (vibration enabled)
    ConfigManager::setInt("Controls.Vibration", controllerIndex);
    return;
  }
  *(uint *)(this + 0x14) = *(uint *)(this + 0x14) | 2; // +0x14: flags, set bit 1 (vibration enabled)
  ConfigManager::setInt("Controls.Vibration", controllerIndex);
  return;
}
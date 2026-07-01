// FUNC_NAME: InputManager::setControllerRumble
void InputManager::setControllerRumble(uint rumbleFlags)
{
  char isInitialized;
  
  isInitialized = InputManager::isInitialized();
  if (isInitialized != '\0') {
    if (((rumbleFlags & 2) != 0) && ((rumbleFlags & 1) == 0)) {
      rumbleFlags = rumbleFlags & 0xfffffffd;
    }
    if (rumbleFlags != 0) {
      InputManager::applyRumble(rumbleFlags);
    }
  }
  return;
}
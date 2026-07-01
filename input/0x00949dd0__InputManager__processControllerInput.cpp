// FUNC_NAME: InputManager::processControllerInput
void InputManager::processControllerInput(void)
{
  int controllerIndex;
  
  controllerIndex = InputManager::getActiveControllerIndex(&stack0x00000004);
  if (-1 < controllerIndex) {
    InputManager::handleControllerInput();
  }
  return;
}
// FUNC_NAME: InputManager::processControllerState
void InputManager::processControllerState(int controllerIndex, int actionMapIndex, int inputData, int outputData)
{
  char localBuffer[44];
  
  FUN_00850be0(inputData, actionMapIndex, localBuffer);
  FUN_00850d80(controllerIndex, inputData, localBuffer, outputData);
  return;
}
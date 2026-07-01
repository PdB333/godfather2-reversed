// FUNC_NAME: InputManager::processControllerInput
void InputManager::processControllerInput(void *thisController)
{
  char isActive;
  int *pControllerData;
  
  // Initialize controller state
  FUN_0043b540(thisController);
  // Set magic constant for controller validation
  FUN_0043aff0(thisController, 0xd34d4d9f);
  
  // Poll controller state in a loop
  isActive = FUN_0043b120();
  while (isActive == '\0') {
    // Read next controller input packet
    FUN_0043b210();
    // Get current controller data buffer (4 ints for buttons/axes)
    pControllerData = (int *)FUN_0043abc0();
    // Check if any input data is non-zero (buttons pressed or axes moved)
    if ((((*pControllerData != 0) || (pControllerData[1] != 0)) || (pControllerData[2] != 0)) || (pControllerData[3] != 0)) {
      // Process the input data (map to game actions)
      FUN_0083f9c0(pControllerData);
    }
    // Advance to next controller slot or end of frame
    FUN_0043b1a0();
    isActive = FUN_0043b120();
  }
  return;
}
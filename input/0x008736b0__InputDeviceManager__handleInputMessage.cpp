// FUNC_NAME: InputDeviceManager::handleInputMessage
undefined4 __thiscall InputDeviceManager::handleInputMessage(int this, undefined4 param_2, undefined4 param_3, undefined4 param_4, int messageType, undefined4 param_6)
{
  undefined4 result;
  int controllerIndex;
  char *buttonState;
  float10 axisX, axisY, axisZ;

  if (messageType == 10) {
    // Controller data update message (e.g., from XInput)
    int statePtr = *(int *)(this + 0x60); // +0x60: current active controller state pointer or index
    if ((statePtr != 0) && (statePtr != 0x48)) {
      // Parse input packet from param_3
      FUN_0086a770(param_3); // likely parse/gather raw input data

      // Compute controller slot base offset (0x48 size per slot?)
      if (statePtr == 0) {
        controllerIndex = 0;
      } else {
        controllerIndex = statePtr + -0x48;
      }

      // Check if this slot has a valid controller connected (offset 0xaa0)
      if (*(int *)(controllerIndex + 0xaa0) != 0) {
        // Read thumbstick axes
        axisX = (float10)FUN_00549a20(); // get left stick X
        FUN_0086b830((float)axisX);     // set left stick X output

        axisY = (float10)FUN_00549a10(); // get left stick Y
        FUN_0086b7d0((float)axisY);     // set left stick Y output

        axisZ = (float10)FUN_00549a00(); // get right stick X? or trigger?
        FUN_0086b7b0((float)axisZ);     // set right stick X output

        // Read button states as booleans
        buttonState = (char *)FUN_00549a30(&param_3); // get button A state
        FUN_0086b7f0(*buttonState != '\0');           // set button A

        buttonState = (char *)FUN_00549a40(&param_3); // get button B state
        FUN_0086b810(*buttonState != '\0');           // set button B
      }
    }
    return 1;
  }

  if (messageType != 0xb) {
    // Delegate to base class handler for unknown message types
    result = FUN_004ac700(param_2, param_3, param_4, messageType, param_6);
    return result;
  }

  // Message type 11: possibly controller disconnect or reset
  FUN_00624d00(); // clean up / reset controller state
  return 1;
}
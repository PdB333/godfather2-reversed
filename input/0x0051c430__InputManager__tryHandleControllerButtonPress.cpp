// FUNC_NAME: InputManager::tryHandleControllerButtonPress

void InputManager::tryHandleControllerButtonPress(void *this, undefined4 param_2)
{
  short controllerCount;
  int *controllerDataPtr;
  int controllerIndex;
  char buttonHandled;
  
  controllerCount = *(short *)((int)this + 0x80); // +0x80: number of controller slots
  controllerIndex = 0;
  if (0 < controllerCount) {
    controllerDataPtr = (int *)((int)this + 0xf4); // +0xf4: array of controller data pointers (each entry is 0x14 bytes apart)
    do {
      if (*controllerDataPtr != 0) {
        // Call vtable+0x30 which is likely a function to check if a button was pressed on this controller
        buttonHandled = (**(code **)(*(int *)*controllerDataPtr + 0x30))(param_2);
        if (buttonHandled != '\0') {
          return; // Button was handled, stop processing
        }
      }
      controllerIndex = controllerIndex + 1;
      controllerDataPtr = controllerDataPtr + 5; // Each controller data entry is 5 ints (0x14 bytes) apart
    } while (controllerIndex < controllerCount);
  }
  return;
}
// FUNC_NAME: InputManager::getControllerState
void InputManager::getControllerState(void *this, undefined4 *outState)
{
  undefined4 *controllerSlot;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int fsOffset;
  
  // Get the controller state from the input device manager slots
  // +0x8: controller slot index (offset from this)
  // The slots array is accessed via TLS (Thread Local Storage) at FS:[0x2c]
  controllerSlot = (undefined4 *)(*(int *)(**(int **)(fsOffset + 0x2c) + 8) + 0x80 + *(int *)(this + 8));
  
  // Copy the 16-byte controller state (4 x 4 bytes)
  // slot layout: +0x00: buttons/triggers, +0x04: left thumb X, +0x08: left thumb Y, +0x0C: right thumb X
  uVar2 = controllerSlot[1];
  uVar3 = controllerSlot[2];
  uVar4 = controllerSlot[3];
  *outState = *controllerSlot;
  outState[1] = uVar2;
  outState[2] = uVar3;
  outState[3] = uVar4;
  return;
}
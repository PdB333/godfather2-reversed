// FUNC_NAME: InputManager::resetControllerState
void InputManager::resetControllerState(void)
{
  // Controller slot index (0-based), default to first slot
  int controllerSlot = 1;  // +0x00: slot index
  int unk1 = 0;            // +0x04: unknown
  int unk2 = 0;            // +0x08: unknown
  byte unk3 = 0;           // +0x0c: unknown

  // Call internal reset function with controller state structure
  FUN_005e2440(&controllerSlot);
}
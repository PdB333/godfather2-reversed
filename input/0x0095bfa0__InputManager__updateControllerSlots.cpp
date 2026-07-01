// FUNC_NAME: InputManager::updateControllerSlots
void __fastcall InputManager::updateControllerSlots(int this)
{
  int controllerIndex;
  int controllerData;
  int slotData;
  
  if (this == 0) {
    controllerIndex = 0;
  }
  else {
    controllerIndex = this + 0x54;  // +0x54: offset to controller slot array
  }
  FUN_0097e300(controllerIndex);  // likely updateControllerSlot or readControllerState
  controllerData = FUN_0097b860();  // likely getActiveControllerCount or getNextActiveController
  if (controllerData != 0) {
    slotData = 0;
    controllerIndex = FUN_0097b8b0(0);  // likely getControllerByIndex(0)
    FUN_0095be90(controllerIndex, slotData);  // likely setControllerSlotData or applyControllerConfig
  }
  return;
}
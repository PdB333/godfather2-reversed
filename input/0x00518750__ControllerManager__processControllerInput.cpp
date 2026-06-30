// FUNC_NAME: ControllerManager::processControllerInput
void ControllerManager::processControllerInput(void)
{
  int inputSlot;
  
  inputSlot = ControllerManager::getActiveControllerSlot();
  ControllerManager::processSlotByType(&controllerSlots, controllerSlotData, controllerSlotFlags, 1, 0, inputSlot, 0, 0);
  return;
}
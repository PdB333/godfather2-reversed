// FUNC_NAME: InputDeviceManager::processControllerAction
void InputDeviceManager::processControllerAction(int controllerSlot, unsigned int param2, unsigned int param3) {
    // Validate the controller slot index; if valid (>=0), apply the data
    int result = validateControllerSlot(&controllerSlot);
    if (result >= 0) {
        applyControllerData(param2, param3);
    }
}
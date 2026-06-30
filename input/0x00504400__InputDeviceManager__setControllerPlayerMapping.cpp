// FUNC_NAME: InputDeviceManager::setControllerPlayerMapping
void InputDeviceManager::setControllerPlayerMapping(int mappingValue) {
    // Global singleton pointer to the InputDeviceManager (DAT_0120550c)
    InputDeviceManager* mgr = reinterpret_cast<InputDeviceManager*>(DAT_0120550c);
    // Retrieve the internal controller mapping structure (FUN_00505c90)
    ControllerMapping* mapping = reinterpret_cast<ControllerMapping*>(FUN_00505c90(mgr));
    // +0x8: Field storing the player mapping (e.g., player index or controller slot)
    mapping->mappingValue = mappingValue;
}
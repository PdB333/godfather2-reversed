// FUNC_NAME: InputManager::setControllerDeadZones
void InputManager::setControllerDeadZones(uint32_t controllerIndex, uint32_t flags) {
    // Thresholds for left stick, right stick, and trigger input dead zones
    uint32_t deadZones[3] = {0x20, 0x30, 0x40};
    // Apply thresholds to the specified controller
    applyControllerThresholds(controllerIndex, flags, deadZones, 3);
}
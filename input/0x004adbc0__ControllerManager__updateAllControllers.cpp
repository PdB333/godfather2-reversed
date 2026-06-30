// FUNC_NAME: ControllerManager::updateAllControllers
void ControllerManager::updateAllControllers() {
    uint32_t count = *(uint32_t*)(this + 8); // m_controllerCount at +0x08
    for (uint32_t i = 0; i < count; i++) {
        // Each element in m_ppControllers (at +0x04) is a pointer to a controller object.
        // The controller object has a field at +0x84 (e.g., m_deviceHandle).
        uint32_t handle = *(uint32_t*)(*(int32_t*)(*(int32_t*)(this + 4) + i * 4) + 0x84);
        // Inner loop: for each controller, call update for all indexes (likely redundant in original code)
        // This could represent a nested iteration over all slots (e.g., axes/buttons) but the index is fixed.
        for (uint32_t j = 0; j < count; j++) {
            FUN_004acde0(handle, i); // call per-controller update function with handle and index
        }
    }
}
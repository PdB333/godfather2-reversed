// FUNC_NAME: InputManager::setAnalogInput
void InputManager::setAnalogInput(uint8_t slotIndex, uint8_t byte1, uint8_t byte2) {
    // Check if input processing is active (likely game state check)
    if (!isInputActive()) {
        return;
    }

    uint8_t idx = slotIndex;

    // If target slot matches current active slot and no forced override (0x12 = sentinel), use forced slot instead
    if (slotIndex == m_currentSlot && m_forcedSlot != 0x12) {
        idx = m_forcedSlot;
    }

    // Pointer to the base of the selected controller slot (each slot is 0x44 bytes)
    ControllerSlot* slot = reinterpret_cast<ControllerSlot*>(reinterpret_cast<uint8_t*>(this) + idx * 0x44);

    // Only write if the controller slot is actually connected
    if (slot->isConnected) {
        slot->dataByte1 = byte1;
        slot->dataByte2 = byte2;
    }
}
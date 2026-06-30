// FUNC_NAME: InputDeviceManager::setSlotConnected
void InputDeviceManager::setSlotConnected(unsigned int slotIndex, char status)
{
    // Only 17 slots (0-16) are valid; index 16 might be keyboard/mouse or reserved.
    if (slotIndex < 17) {
        g_connectedSlots[slotIndex] = (status == '\0');
    }
}
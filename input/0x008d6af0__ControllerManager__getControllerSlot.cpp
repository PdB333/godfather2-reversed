// FUNC_NAME: ControllerManager::getControllerSlot
int __thiscall ControllerManager::getControllerSlot(int slotIndex) {
    // +0x44 offset to the start of an array of controller slots,
    // each slot has a size of 0x14 (20 bytes).
    // Returns an integer representing the raw address of the slot.
    return reinterpret_cast<int>(this) + 0x44 + slotIndex * 0x14;
}
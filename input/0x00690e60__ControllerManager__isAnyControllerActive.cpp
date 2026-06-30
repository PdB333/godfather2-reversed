// FUNC_NAME: ControllerManager::isAnyControllerActive
// Function address: 0x00690e60
// Role: Checks if any of the first 4 controller slots are active (e.g., connected or providing input).
// Calls getControllerSlotArray (0x004973e0) to retrieve a pair of base fields,
// then iterates 4 slots using readSlotByte (0x0049a870) and isSlotActive (0x00b930b0).

bool ControllerManager::isAnyControllerActive() {
    uint32* slotArray = getControllerSlotArray(this);
    if (slotArray != nullptr) {
        uint32 baseField0 = slotArray[0];  // +0x00
        uint32 baseField1 = slotArray[1];  // +0x04
        for (uint i = 0; i < 4; i++) {
            char slotByte = readSlotByte(baseField0, baseField1, i);
            if (isSlotActive(slotByte)) {
                return true;
            }
        }
    }
    return false;
}
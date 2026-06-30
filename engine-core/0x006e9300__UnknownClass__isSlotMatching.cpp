// FUNC_NAME: UnknownClass::isSlotMatching
bool __thiscall UnknownClass::isSlotMatching(int requestedSlot) {
    // Check if the object is active (byte at +0xA8)
    if (*(char*)(this + 0xA8) == 0) {
        return false;
    }

    // Slot data at +0x98: seems to be an encoded slot index
    int slotData = *(int*)(this + 0x98);
    if (slotData != 0 && slotData != 0x48) {
        // Decode: subtract base offset 0x48 to get actual slot index
        int actualSlot = (slotData == 0) ? 0 : (slotData - 0x48);
        if (actualSlot != requestedSlot) {
            return false;
        }
    }
    return true;
}
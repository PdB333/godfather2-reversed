// FUNC_NAME: initControllerSlotArray
// Function at 0x00609b20: Initializes an array of 32 controller slots (each 12 bytes) to zero, and resets a global count. Returns pointer to the array base.
// The slot structure appears to be: two 4-byte fields (likely state/ID) and a 1-byte field (active flag?), with 3 bytes padding to 12 bytes total.

struct ControllerSlot {
    int field0;      // +0x00
    int field1;      // +0x04
    byte field2;     // +0x08
    byte pad[3];     // +0x09 (padding to 12 bytes)
};

// Global array of 32 slots (base at 0x01222328)
// Global count at 0x012224a8

ControllerSlot* initControllerSlotArray() {
    ControllerSlot* slotArray = reinterpret_cast<ControllerSlot*>(0x01222328);
    int count = 32; // 0x1f + 1

    // Iterate over slots, zeroing each field
    for (int i = 0; i < count; ++i) {
        slotArray[i].field0 = 0;
        slotArray[i].field1 = 0;
        slotArray[i].field2 = 0;
    }

    // Reset global count (e.g., number of active slots)
    *(int*)0x012224a8 = 0;

    return slotArray;
}
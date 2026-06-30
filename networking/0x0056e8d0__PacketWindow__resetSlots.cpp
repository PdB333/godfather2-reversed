// FUNC_NAME: PacketWindow::resetSlots
void __thiscall PacketWindow::resetSlots(void) {
    // +0x0C: count of slots
    int slotCount = *(int*)((char*)this + 0x0C);
    // +0x10: array of slot pairs (each pair: sequence, state)
    int* slotArray = (int*)((char*)this + 0x10);
    // Global constant (likely invalid sequence or default state)
    int defaultState = DAT_00e2b1a4;

    for (int i = 0; i < slotCount; i++) {
        slotArray[i * 2] = 0xFFFFFFFF;      // invalid sequence number
        slotArray[i * 2 + 1] = defaultState; // default state value
    }
}
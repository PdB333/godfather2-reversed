// FUNC_NAME: TNLConnection::initWindowSlots
void __thiscall TNLConnection::initWindowSlots(int this) {
    int slotIndex;
    int *slotPtr;

    slotIndex = 31;
    slotPtr = (int *)(this + 8);
    do {
        slotPtr[1] = 0;  // slot field at +12
        *slotPtr = 0;    // slot field at +8
        slotPtr[-1] = 0; // slot field at +4
        slotPtr[-2] = 0; // slot field at +0
        slotPtr[2] = 0;  // slot field at +16
        slotPtr[3] = 0;  // slot field at +20
        slotPtr = slotPtr + 6; // move to next slot (24 bytes)
        slotIndex = slotIndex - 1;
    } while (-1 < slotIndex);
    *(int *)(this + 0x300) = 0; // extra field after the array (offset 768)
}
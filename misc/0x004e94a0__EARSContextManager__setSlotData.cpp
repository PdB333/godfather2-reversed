// FUNC_NAME: EARSContextManager::setSlotData

void __thiscall EARSContextManager::setSlotData(const int data[4], int extraValue) {
    // Retrieve thread-local storage pointer from FS:[0x2c] (EA EARS engine per-thread context)
    int* tlsBase = **(int***)(__readfsdword(0x2c) + 0x2c);
    // tlsBase points to a context structure; +8 holds a secondary buffer pointer
    int* bufferBase = *(int**)((char*)tlsBase + 8);

    // This object stores a slot offset at +0x18 (byte offset into the buffer)
    int slotOffset = *(int*)((char*)this + 0x18);

    // First slot at bufferBase + 0x40 + slotOffset: write 16-byte data (likely 4 floats/ints)
    int* slot1 = (int*)((char*)bufferBase + 0x40 + slotOffset);
    slot1[0] = data[0];
    slot1[1] = data[1];
    slot1[2] = data[2];
    slot1[3] = data[3];

    // Call internal flush/notification routine (possibly synchronizes pending writes)
    FUN_004aab40();

    // Second slot at bufferBase + 0x88 + slotOffset: write the extra value
    int* slot2 = (int*)((char*)bufferBase + 0x88 + slotOffset);
    *slot2 = extraValue;
}
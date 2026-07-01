// FUNC_NAME: PacketQueue::addPacket
void __thiscall PacketQueue::addPacket(int this, int id, int* data) {
    // Check if the data is valid (FUN_008b7bb0 returns negative if invalid)
    int result = isValidData(data);
    if (result < 0) {
        // If queue is full (count == 64), flush it
        if (*(int*)(this + 0x508) == 0x40) {
            flushQueue(0); // FUN_008b7a40 – likely empties the buffer
        }
        // Get current count and increment
        int index = *(int*)(this + 0x508);
        *(int*)(this + 0x508) = index + 1;
        // Write entry at offset 0x8 + index * 0x14 (20 bytes per entry)
        int* entry = (int*)(this + 8 + index * 0x14);
        entry[0] = id;                                    // +0x00: entry ID
        entry[1] = data[0];                               // +0x04: data word 0
        entry[2] = data[1];                               // +0x08: data word 1
        entry[3] = data[2];                               // +0x0c: data word 2
        entry[4] = data[3];                               // +0x10: data word 3
    }
    // If data is valid, do nothing (entry not added)
}
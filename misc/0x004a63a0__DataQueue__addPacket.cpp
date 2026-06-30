// FUNC_NAME: DataQueue::addPacket
void __thiscall DataQueue::addPacket(uint32_t dataLow, uint32_t dataHigh)
{
    int capacity = *(int *)(this + 0x7C);   // +0x7C: maximum number of packets
    int count    = *(int *)(this + 0x78);   // +0x78: current number of stored packets

    // Grow buffer if full
    if (count == capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        resizeBuffer(newCapacity);          // FUN_004a7fb0 – reallocate internal buffer
    }

    // Compute address of the new 8-byte slot (two 32-bit words)
    uint32_t *slot = (uint32_t *)(*(int *)(this + 0x74) + count * 8); // +0x74: base pointer of packet array

    // Update count BEFORE write (matching original)
    *(int *)(this + 0x78) = count + 1;

    // Store the two parts; note that only the high 16 bits of dataHigh are kept
    if (slot) {
        slot[0] = dataLow;                     // first half (e.g., packet data)
        slot[1] = dataHigh & 0xFFFF0000;       // second half (e.g., timestamp with low bits zeroed)
    }
}
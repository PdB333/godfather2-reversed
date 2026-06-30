// FUNC_NAME: NetConnection::initPacketWindow
void NetConnection::initPacketWindow(void)
{
    // Clear the first 8 bytes of each of the 32 packet window slots.
    // Each slot is 16 bytes; only the first two dwords are zeroed.
    // The slot array starts at offset +0x8 from this.
    int slotCount = 0x1f; // 32 slots (loop runs while >= 0)
    uint32_t* slotPtr = (uint32_t*)(this + 0x8);
    do {
        slotPtr[0] = 0;
        slotPtr[1] = 0;
        slotPtr += 4; // Advance by 16 bytes (4 * sizeof(uint32_t))
        slotCount--;
    } while (slotCount >= 0);
}
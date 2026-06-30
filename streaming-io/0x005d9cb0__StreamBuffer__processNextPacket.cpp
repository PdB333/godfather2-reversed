// FUNC_NAME: StreamBuffer::processNextPacket
void StreamBuffer::processNextPacket(void) {
    uint32_t readPtr = *(uint32_t *)(this + 0x8); // +0x8: m_readPtr
    if (readPtr != 0) {
        uint32_t writePtr = *(uint32_t *)(this + 0xC); // +0xC: m_writePtr
        int32_t diff = (int32_t)(writePtr - readPtr);
        // Check if at least one packet of size 0x28 exists
        int32_t count = diff / 0x28;
        int32_t sign = diff >> 0x1F; // sign extension for negative
        if (count + sign != sign) {
            if (writePtr < readPtr) {
                FUN_00b97aea(); // assertion failed
            }
            if (*(uint32_t *)(this + 0xC) < *(uint32_t *)(this + 0x8)) {
                FUN_00b97aea(); // assertion failed again
            }
            // Retrieve next packet parameters (12-byte temp buffer)
            uint32_t *packetParams = (uint32_t *)FUN_005da4d0(local_c, 0);
            // Process the packet: this, param0, param1, this, writePtr
            FUN_005da180(this, packetParams[0], packetParams[1], this, writePtr);
        }
    }
    return;
}
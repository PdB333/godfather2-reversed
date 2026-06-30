// FUNC_NAME: AckWindow::areAllAcksPresent
int AckWindow::areAllAcksPresent()
{
    int state = this->state; // +0x00: 0=invalid, 1=initial, >1=active
    if (state == 0 || state == 1) {
        return state;
    }

    // state > 1: get the current end index of the ack range
    int endIndex = getCurrentAckRangeEnd(); // FUN_00665d40 (global or static)
    int bitIndex = 0x1C; // start checking from bit 28 (base of sliding window)

    if (endIndex > 0x1C) {
        uint32_t* bitmaskWord = (uint32_t*)(this->bitmaskPtr + 4); // +0x0C: pointer to bitmask struct, skip 4 bytes to the array
        uint32_t currentBit = 1;

        for (; bitIndex < endIndex; ++bitIndex) {
            if ((*bitmaskWord & currentBit) == 0) {
                return 0; // missing ack
            }
            currentBit <<= 1;
            if (currentBit > 0x0FFFFFFF) { // after bit 28, advance to next word
                ++bitmaskWord;
                currentBit = 1;
            }
        }
    }

    return 1; // all acks present
}
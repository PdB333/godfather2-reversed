// FUNC_NAME: BitFieldManager::addToNibbleSlot
void __thiscall BitFieldManager::addToNibbleSlot(int addValue, int slotIndex) {
    // offset +0xCC holds a 32-bit bitfield with 8 nibble slots (4 bits each)
    // slotIndex must be 0-7
    uint32_t shift = (slotIndex & 0x7) * 4;                // slot * 4, masked to avoid high bits
    uint32_t currentNibble = (this->packedNibbles >> shift) & 0xF;
    uint32_t newNibble = currentNibble + addValue;
    if (newNibble > 0xF) {
        newNibble = 0xF;                                   // clamp to max value 15
    }
    // clear the nibble, then write new value
    this->packedNibbles = (this->packedNibbles & ~(0xF << shift)) | (newNibble << shift);
}
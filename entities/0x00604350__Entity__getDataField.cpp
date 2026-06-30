// FUNC_NAME: Entity::getDataField
// Address: 0x00604350
// This function reads a 32-bit value from a nested pointer structure.
// It dereferences the pointer at this+0x20 (likely an EntityData*), then reads offset 0xA4 from that data block.
uint32_t Entity::getDataField() const {
    // Get the pointer at this+0x20 (e.g., mDataBlock)
    uint32_t* dataBlock = *reinterpret_cast<uint32_t**>(reinterpret_cast<const uint8_t*>(this) + 0x20);
    // Read the 32-bit value at offset +0xA4 within the data block
    return *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(dataBlock) + 0xA4);
}
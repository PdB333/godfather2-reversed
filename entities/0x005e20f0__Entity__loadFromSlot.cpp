// FUNC_NAME: Entity::loadFromSlot
bool Entity::loadFromSlot(uint slotIndex, SourceData* sourceArray) {
    // Check slot index validity (0-4)
    if (slotIndex >= 5) {
        return false;
    }

    // Calculate pointer to the specific slot in the source array
    SourceData* slotData = reinterpret_cast<SourceData*>(
        reinterpret_cast<uint8_t*>(sourceArray) + slotIndex * sizeof(SourceData)
    );

    // Copy data from the slot into this object
    // +0x14: byte field (e.g., character type flag)
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(this) + 0x14) =
        *reinterpret_cast<uint8_t*>(reinterpret_cast<uint8_t*>(slotData) + 0x494);

    // +0x18: 32-bit field (e.g., health value)
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x18) =
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(slotData) + 0x210);

    // Call sub-object initializer at offset 0x498
    FUN_004d3e20(reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(slotData) + 0x498));

    // +0x10: 32-bit field (e.g., max health)
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x10) =
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(slotData) + 0x490);

    // +0x1c: 32-bit field (e.g., armor value)
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x1c) =
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(slotData) + 0x1f8);

    return true;
}
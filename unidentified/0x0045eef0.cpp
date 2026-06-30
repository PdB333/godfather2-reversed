// FUN_NAME: Entity::getTypeDescriptor
// Function at 0x0045eef0: Reads a pointer at offset 0x218 from 'this', combines its upper 24 bits with a byte at offset 0x30 of the pointed object.
// Used by multiple caller functions (0x720560, 0x71ef20, etc.) likely for type/ID extraction.
int Entity::getTypeDescriptor() {
    // +0x218: Pointer to a subordinate data structure (e.g., type info or properties)
    uint32_t* pData = *(uint32_t**)(this + 0x218);

    // High 24 bits of the pointer value (ID or flag portion)
    uint32_t high24 = (uint32_t)pData >> 8;

    if (pData != nullptr) {
        // +0x30: Type/subtype byte from the pointed structure
        uint8_t lowByte = *(uint8_t*)(pData + 0x30);
        // Combine: (high24 << 8) | lowByte  (low byte replaced)
        return (high24 << 8) | lowByte;
    } else {
        // Null pointer => return 0 (high 24 bits zeroed)
        return high24 << 8; // always 0
    }
}
// FUNC_NAME: TNLConnection::checkReliableSlot
uint __fastcall TNLConnection::checkReliableSlot(TNLConnection* const this, uint mask) {
    uint result = mask & 0xFFFFFF00;

    int slotId = *(int*)(reinterpret_cast<uint8*>(this) + 4);
    if (slotId != 0 && slotId != 0x48) {
        uint8 subIndex = (*(uint8*)(reinterpret_cast<uint8*>(this) + 0x12) + 1) % 12;
        if (slotId != 0) { // always true due to outer condition
            int slotOffset = slotId - 0x48;
            // +0x1e20: tag array (12 entries per slot? actually linear indexing)
            bool isFree = (*(reinterpret_cast<char*>(this) + 0x1e20 + subIndex + slotOffset) == '\0');
            return (static_cast<uint>(slotOffset >> 8) << 8) | (isFree ? 1u : 0u);
        }
        // dead code branch
        result = (uint)(*(reinterpret_cast<char*>(this) + 0x1e20 + subIndex) == '\0');
    } else {
        result = (uint)(*(reinterpret_cast<char*>(this) + 0x1e20 + result) == '\0');
    }
    return result;
}
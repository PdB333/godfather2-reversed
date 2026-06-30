// FUNC_NAME: TNLConnection::dispatchPacket
// Address: 0x00641470
// Handles incoming packet dispatch, specifically type 0xc (12) which appears to set a flag in an array.

// Forward declarations of helper member functions
void TNLConnection::readHeader(int &outType, int &outIndex);
void TNLConnection::handleOtherPackets();

void TNLConnection::dispatchPacket() {
    // +0x1c: pointer to connection's internal data buffer (e.g., packet receive info)
    int *pData = *reinterpret_cast<int**>(this + 0x1c);
    
    int packetType;
    int slotIndex;
    readHeader(packetType, slotIndex);
    
    if (packetType == 0xc) {
        // For packet type 12, update a flag array at offset 0xc from the data buffer
        // *pData points to a structure; offset 0xc holds a pointer to an array of uint32 flags
        uint32_t *flagsArray = reinterpret_cast<uint32_t*>(
            *reinterpret_cast<int*>(*pData + 0xc)
        );
        // Clear bits 7–14 (mask 0xffff807f) and set bit 6 (0x40)
        flagsArray[slotIndex] = (flagsArray[slotIndex] & 0xffff807f) | 0x40;
        return;
    }
    // Other packet types go to generic handler
    handleOtherPackets();
}
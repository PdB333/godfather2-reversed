// FUNC_NAME: NetPacket::initializeHeader
void __thiscall NetPacket::initializeHeader(uint32_t typeOrSeq, uint32_t ackOrSize, char reliableFlag, uint32_t mask, uint32_t extraData) {
    bool isSessionActive = false;

    // Global pointer to the network session (e.g., g_netSession)
    if (DAT_0112ebb4 != 0) {
        // Check if session is connected (byte at offset 0x124 likely m_bConnected)
        if (*(char*)(DAT_0112ebb4 + 0x124) != '\0') {
            char sessionActive = FUN_0089c630(); // Session::isActive()
            if (sessionActive != '\0') {
                isSessionActive = true;
            }
        }
    }

    // +0x00: packet type or sequence number
    this->field0 = typeOrSeq;

    // +0x04: ACK or size – set to 0 if session not active or reliableFlag not set
    if (isSessionActive || reliableFlag == '\0') {
        ackOrSize = 0;
    }
    this->field4 = ackOrSize;

    // +0x10: mask, only stored if session is active (bitwise AND)
    this->field10 = -(uint)isSessionActive & mask;

    // +0x0C: extra data – only set if session active AND reliableFlag set
    if (isSessionActive && reliableFlag != '\0') {
        this->extraData = extraData;
        this->reliableFlag = reliableFlag; // +0x08
        this->versionOrType = 1;           // +0x14
    } else {
        this->extraData = 0;
        this->reliableFlag = reliableFlag; // +0x08
        this->versionOrType = 1;           // +0x14
    }

    // Note: struct layout (24 bytes):
    // +0x00: uint32 field0
    // +0x04: uint32 field4
    // +0x08: char   reliableFlag
    // +0x0C: uint32 extraData
    // +0x10: uint32 field10 (masked)
    // +0x14: char   versionOrType (always 1)
    // padding to 24 bytes likely
}
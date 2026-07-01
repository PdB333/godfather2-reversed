// FUNC_NAME: TNLConnection::resetSendWindow
void TNLConnection::resetSendWindow() {
    // Clear the 12-slot send window (offset +0x50 to +0x7C)
    m_sendWindowSlots[0] = 0; // +0x50
    m_sendWindowSlots[1] = 0; // +0x54
    m_sendWindowSlots[2] = 0; // +0x58
    m_sendWindowSlots[3] = 0; // +0x5C
    m_sendWindowSlots[4] = 0; // +0x60
    m_sendWindowSlots[5] = 0; // +0x64
    m_sendWindowSlots[6] = 0; // +0x68
    m_sendWindowSlots[7] = 0; // +0x6C
    m_sendWindowSlots[8] = 0; // +0x70
    m_sendWindowSlots[9] = 0; // +0x74
    m_sendWindowSlots[10] = 0; // +0x78
    m_sendWindowSlots[11] = 0; // +0x7C
}
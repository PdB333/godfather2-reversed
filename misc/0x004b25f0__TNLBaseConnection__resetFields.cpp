// FUNC_NAME: TNLBaseConnection::resetFields
void TNLBaseConnection::resetFields(TNLBaseConnection* this) {
    // Clear main network state fields (offsets based on object layout)
    *(int*)((char*)this + 0x00) = 0;   // +0x00: m_sequenceLocal (send sequence)
    *(int*)((char*)this + 0x04) = 0;   // +0x04: m_sequenceRemote (recv sequence)
    *(int*)((char*)this + 0x08) = 0;   // +0x08: m_lastAckSequence

    *(char*)((char*)this + 0x8C) = 0;  // +0x8C: m_controlFlags (byte 0)
    *(char*)((char*)this + 0x8D) = 1;  // +0x8D: m_connectionActive (set active)

    *(int*)((char*)this + 0x90) = 0;   // +0x90: m_pingTime
    *(char*)((char*)this + 0x94) = 0;  // +0x94: m_connectionState

    *(int*)((char*)this + 0x98) = 0;   // +0x98: m_timeoutInterval
    *(int*)((char*)this + 0x9C) = 0;   // +0x9C: m_lastPacketTime
    *(int*)((char*)this + 0xA0) = 0;   // +0xA0: m_estimatedRTT
    *(int*)((char*)this + 0xA4) = 0;   // +0xA4: m_outstandingPackets
    *(int*)((char*)this + 0xA8) = 0;   // +0xA8: m_packetsSent
    *(int*)((char*)this + 0xAC) = 0;   // +0xAC: m_packetsReceived

    *(char*)((char*)this + 0x0C) = 0;  // +0x0C: m_linkSpeedClass (byte)

    // Base class or common network object initialization
    FUN_004b1f30();  // likely NetObject::initBase()

    // Final flag to indicate initialization complete
    *(char*)((char*)this + 0x904) = 1;  // +0x904: m_readyForGhosting
}
// FUNC_NAME: NetSession::processReceiveQueue
void __thiscall NetSession::processReceiveQueue(void) {
    // this: pointer to NetSession object
    // offsets: +0x08 = m_nPendingSize (decremented by 8 each call)
    // +0x10 = m_pReceiveBuffer (pointer to buffer state struct)
    // Buffer state at m_pReceiveBuffer:
    //   +0x20 = m_nReadIndex (head)
    //   +0x24 = m_nWriteIndex (tail)

    acquireBufferLock(); // FUN_00627b40

    // Check if there is data available (read index <= write index)
    if (m_pReceiveBuffer->m_nReadIndex <= m_pReceiveBuffer->m_nWriteIndex) {
        processIncomingPacket(); // FUN_00627360
    }

    PacketHeader header; // stack variable at offset 0x08 (8 bytes)
    readPacketHeader(&header); // FUN_00636910

    // Check again after header read (maybe new data arrived or buffer updated)
    if (m_pReceiveBuffer->m_nReadIndex <= m_pReceiveBuffer->m_nWriteIndex) {
        processIncomingPacket(); // FUN_00627360
    }

    validatePacket(); // FUN_006343b0
    m_nPendingSize -= 8; // consume 8 bytes (packet header size)
    updateSequence(); // FUN_006338a0

    return;
}
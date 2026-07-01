// FUNC_NAME: NetSession::processIncomingPacket
bool NetSession::processIncomingPacket(Packet* packet, uint param)
{
    // Validate the packet (e.g., checksum or ID check)
    if (!Packet::validate(packet, param)) {
        return false;
    }

    param = 0;
    // Dispatch the packet with a hash identifier (0xd80c71d2)
    if (packet->vtable->dispatch(0xd80c71d2, &param) && /* some condition on param? */ true) {
        // Successful dispatch – handle reliable packet processing and state updates
        processReliablePacket();

        // Update connection (e.g., flush outgoing data) via vtable call on m_connection
        (*(m_connection->vtable + 0x8))();

        // Check if bit 2 (0x4) of m_flags was set; if so, clear it and signal
        if ((m_flags & 0x4) != 0) {
            // Call event manager to signal event 0x10 (e.g., disconnect pending cleared)
            (*(m_eventManager->vtable + 0x28))(0x10);
            m_flags &= ~0x4u;
        }

        // Release temporary objects (likely reference counting)
        MemoryManager::release(/* temp object */);
        MemoryManager::release(/* temp object */);
    } else {
        // Dispatch failed – check connection status
        if (isConnected()) {
            disconnect(packet);
        }
    }

    // Cleanup: destroy the packet
    packet->vtable->destroy();
    freePacket(packet);
    return true;
}
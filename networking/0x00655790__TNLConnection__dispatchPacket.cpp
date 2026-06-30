// FUNC_NAME: TNLConnection::dispatchPacket
void __thiscall TNLConnection::dispatchPacket(TNLConnection *this, int connectionId, PacketBuffer *packet)
{
    int command;
    int *refCountedObj;
    int localBuffer[2];

    if (packet->currentSize < packet->totalSize) {
        localBuffer[0] = (int)this;
        if ((packet->flags & 0x80) == 0) {
            // Read command byte (0-7) from packet
            command = readIntFromPacket(8, localBuffer);
            if (7 < (byte)command) {
                // If command >= 8, call virtual handler
                (this->vtable->handleLargeCommand)(connectionId, command, packet);
                return;
            }
            switch(command & 0xff) {
            case 0: // Connection request
                handleConnect(this, connectionId);
                return;
            case 1: // Disconnect
                handleDisconnect(this);
                return;
            case 2: // Data payload
                handleData(this, connectionId, packet);
                return;
            case 3: // Ack
                handleAck(this, connectionId);
                return;
            case 4: // Ping?
                handlePing(connectionId);
                return;
            case 5: // Reliable data
                handleReliableData(this, packet);
                return;
            case 6: // Time sync
                handleTimeSync(this, connectionId, packet);
                return;
            case 7: // Sequence
                handleSequence(this, connectionId, packet);
            }
        }
        else {
            // Ref-counted packet object (bit 7 set)
            refCountedObj = getPacketPoolObject();
            if (refCountedObj != nullptr) {
                refCountedObj->refCount += 1;
                processRefCountedPacket(packet);
                refCountedObj->refCount -= 1;
                if (refCountedObj->refCount == 0) {
                    // Free object via virtual destructor at vtable+8
                    (refCountedObj->vtable->destroy)();
                }
            }
        }
    }
    return;
}
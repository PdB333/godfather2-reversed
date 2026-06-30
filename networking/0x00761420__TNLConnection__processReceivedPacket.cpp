// FUNC_NAME: TNLConnection::processReceivedPacket
bool __thiscall TNLConnection::processReceivedPacket(TNLConnection* this, PacketHeader* packet, NetSession* session, float* outLatency)
{
    int bitStream[2]; // local_c (BitStream object on stack)
    int tempValue; // local_4

    // Check if this packet's sequence (stored at packet+0x0A) has already been acknowledged
    if ((*(uint*)((int)this + 0x20) & (uint)*(ushort*)((int)packet + 10)) != 0) {
        return false;
    }

    // Calculate pointer to the ghost entry for the packet's channel index (packet+0x06)
    int ghostEntryPtr = *(int*)((int)session + 0x20) + (uint)*(ushort*)((int)packet + 6) * 0x24;

    // Initialize a BitStream from the packet's payload
    FUN_005fd1c0(bitStream, packet); // BitStream::readFromPacket

    // Default return flag stored in the first byte of the packet struct
    packet->success = 1;

    // Check if the connection is active (this+0x04 is not null and not a special state 0x48)
    if (*(int*)((int)this + 4) != 0 && *(int*)((int)this + 4) != 0x48) {
        if (bitStream[0] == 0) {
            return true; // Nothing to process, but still report success
        }

        // Get network manager singleton and attempt to process the packet data
        int netMgrBase = FUN_00471610(); // e.g. NetSession::getInstance
        bool processResult = FUN_00760020(netMgrBase + 0x30, ghostEntryPtr, &tempValue);

        if (!processResult) {
            // Compute latency/RTT using the ghost entry and the packet's sequence number
            float10 computedLatency = (float10)FUN_00760570(ghostEntryPtr, tempValue, *(int*)packet);
            *outLatency = (float)computedLatency;
        } else {
            // Mark failure in the packet
            packet->success = 0;
        }
    }

    // Destroy the BitStream if it was initialized (bitStream[0] is a allocation flag)
    if (bitStream[0] != 0) {
        FUN_004daf90(bitStream); // BitStream::~BitStream
    }

    return packet->success != 0;
}
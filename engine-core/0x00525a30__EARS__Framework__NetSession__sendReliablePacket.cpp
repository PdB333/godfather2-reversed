// FUNC_NAME: EARS::Framework::NetSession::sendReliablePacket
void __thiscall NetSession::sendReliablePacket(uint32_t this_ptr, uint32_t packetType, int connectionHandle, uint32_t param4, uint32_t param5, uint32_t* dataBuffer)
{
    int connectionObj = 0;
    connectionObj = getObjectByHandle(connectionHandle);
    if ((connectionHandle != 0) && (connectionObj != 0))
    {
        // Check connection state flag at +0xAC (bit 1: disconnected?)
        if ((*(byte*)(connectionObj + 0xAC) & 2) == 0)
            return;
    }

    uint32_t seq1 = getNextPacketSequence();
    if (seq1 != 0)
    {
        uint32_t localBuffer[16]; // 64 bytes for packet payload
        memcpy(localBuffer, dataBuffer, sizeof(localBuffer));

        uint32_t seq2 = getNextPacketSequence();
        uint32_t seq3 = getNextPacketSequence();
        sendPacketInternal(gNetSession, seq1, seq2, seq3, localBuffer, packetType, connectionObj, param4, param5);
    }
}
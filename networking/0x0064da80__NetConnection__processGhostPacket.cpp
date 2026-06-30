// FUNC_NAME: NetConnection::processGhostPacket
void __thiscall NetConnection::processGhostPacket(BitStream* stream, NetConnection* remoteConn)
{
    // Validate settings: only allow ghost processing if the remote connection has
    // appropriate ghost lists and this connection is in the expected state.
    // State 1 = maybe "receiving creates", state 2 = "receiving updates", state 3 = "closed".
    bool invalid = false;
    if ( (remoteConn->mCreateGhostList != nullptr && this->mConnectionState != 1) ||
         (remoteConn->mGhostUpdateList != nullptr && this->mConnectionState != 2) )
    {
        if (this->mConnectionState != 3)
            invalid = true;
    }
    if (!invalid)
    {
        _printErrorMessage("Invalid Packet.");
        return;
    }

    // Read first bit from stream. If not set, no ghost data follows.
    if (!stream->readBit())
        return;

    // Read a 10-bit ghost index.
    int ghostIndex = stream->readInt(10); // 0 to 1023
    ghostIndex &= 0x3FF;

    // Call the virtual packet handler (vtable offset +4) – dispatches to method for this ghost.
    void (*handler)(BitStream*) = reinterpret_cast<void(*)(BitStream*)>( *(void**)(*(int*)this->mPacketHandler + 4) );
    handler(stream);

    // Read a second bit from the stream.
    uint32_t currentBitPos = stream->mReadPos;         // +0x18
    if (currentBitPos >= stream->mBitCount)            // +0x2c
    {
        stream->mError = 1;                             // +0x1c
        return;
    }
    uint8_t byteVal = *(uint8_t*)(stream->mBuffer + (currentBitPos >> 3)); // +0xc
    stream->mReadPos = currentBitPos + 1;
    bool secondBitSet = (byteVal >> (currentBitPos & 7)) & 1;

    if (secondBitSet)
    {
        // Release ghost from remote connection's "create receive" list (size 0x30 per entry)
        void* ghostPtr = *(void**)( *(int*)(remoteConn + 0x214) + ghostIndex * 0x30 );
        _releaseGhost(ghostPtr);
        return;
    }

    // Otherwise release from the standard update list (size 4 per entry)
    if (ghostIndex == -1)
    {
        _releaseGhost(nullptr);
    }
    else
    {
        void* ghostPtr = *(void**)( *(int*)(remoteConn + 0x210) + ghostIndex * 4 );
        _releaseGhost(ghostPtr);
    }
}
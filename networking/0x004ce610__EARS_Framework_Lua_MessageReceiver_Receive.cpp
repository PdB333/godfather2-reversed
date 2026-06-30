// Xbox PDB: EARS::Framework::Lua::MessageReceiver::Receive
// FUNC_NAME: TNLConnection::sendMessage
void __thiscall TNLConnection::sendMessage(int this, const char* messageType, const char* messageData, int messageValue)
{
    // +0x2c: pointer to bitstream/buffer object
    int* bitstream = *(int**)(this + 0x2c);
    
    // Log the message receive operation
    writeString(bitstream, "MessageReceiverReceive");
    
    // Get a temporary buffer pointer and copy its contents to the end of the current write position
    // This likely handles checksum or header duplication
    int* tempBuffer = (int*)getBuffer(bitstream, bitstream + 0x40, *(int*)(bitstream + 8) - 8, 0);
    int* writePtr = *(int**)(bitstream + 8);
    *(int*)(writePtr - 2) = tempBuffer[0];
    *(int*)(writePtr - 1) = tempBuffer[1];
    
    // Write a float type (type 3) with the sequence number from this+0x30
    int* currentWrite = *(int**)(bitstream + 8);
    *currentWrite = 3; // type identifier for float
    *(float*)(currentWrite + 1) = (float)(*(int*)(this + 0x30)); // sequence number
    *(int*)(bitstream + 8) += 8;
    
    // Write the message type string
    writeString(bitstream, messageType);
    
    // Write the message data string (or null if empty)
    if (*messageData == '\0') {
        int* nullWrite = *(int**)(bitstream + 8);
        *nullWrite = 0; // null string marker
        *(int*)(bitstream + 8) += 8;
    } else {
        writeString(bitstream, messageData);
    }
    
    // Write the integer value (type 2) or null if zero
    int* intWrite = *(int**)(bitstream + 8);
    if (messageValue == 0) {
        *intWrite = 0; // null marker
    } else {
        *intWrite = 2; // type identifier for int
        *(intWrite + 1) = messageValue;
    }
    *(int*)(bitstream + 8) += 8;
    
    // Calculate packet start and send
    int packetStart = *(int*)(bitstream + 8) - 0x28; // start of packet data
    int packetSize = packetStart - *(int*)(bitstream + 0x1c); // size from base to current
    int packetInfo[2] = { packetStart, 0 };
    sendPacket(&g_packetHandler, packetInfo, packetSize);
    releaseBuffer();
}
// FUNC_NAME: PacketManager::buildAndSendReliablePacket
void PacketManager::buildAndSendReliablePacket(int channelId, int someParam, int extraParam)
{
    int sequenceNumber;
    byte packetBuffer[44]; // 0x2C bytes for reliable packet header
    sequenceNumber = getNextSequence(); // FUN_00471610 - retrieve next sequence number
    buildReliablePacket(someParam, sequenceNumber, packetBuffer); // FUN_00850be0 - serialize reliable packet data
    sendReliablePacket(channelId, packetBuffer, extraParam); // FUN_00850d80 - send the constructed packet
    return;
}
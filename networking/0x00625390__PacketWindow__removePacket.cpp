// FUNC_NAME: PacketWindow::removePacket
int PacketWindow::removePacket(int sequence, int ack)
{
    uint slotIndex = 0;
    int *packetData = this->packetData + 0x21; // +0x84 base for packet data array

    while (true) {
        if (0x1f < slotIndex) {
            return 0; // not found
        }
        // Check if slot is active, matches sequence, ack, and remote ack
        if ((((*(char *)(slotIndex + 0x184 + (int)this) != '\0') && (sequence == packetData[-0x20])) &&
            (ack == *packetData)) && (remoteAck == packetData[0x20])) break;
        slotIndex = slotIndex + 1;
        packetData = packetData + 1;
    }
    // Clear the slot and decrement count
    *(char *)(slotIndex + 0x184 + (int)this) = 0; // +0x184 slot active flags
    this->count = this->count - 1; // +0x00 count of active packets
    return 1; // removed successfully
}
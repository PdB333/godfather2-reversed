//FUNC_NAME: TNLConnection::buildPacketHeader
void TNLConnection::buildPacketHeader(uint32_t *outSize, PacketInfo *info, uint8_t *outBuffer)
{
    // Check if packet type is valid (0 or 1)
    if (info->type == 0 || info->type == 1) {
        uint16_t sequence = info->sequence;
        uint32_t timestamp = info->timestamp;

        // Build header: first 2 bytes = 2 (packet type marker?)
        *(uint16_t *)outBuffer = 2;
        // Next 2 bytes = sequence in network byte order
        *(uint16_t *)(outBuffer + 2) = htons(sequence);
        // Next 4 bytes = timestamp in network byte order
        *(uint32_t *)(outBuffer + 4) = htonl(timestamp);

        // Set total header size (16 bytes, including padding or additional fields)
        *outSize = 0x10;
    }
}
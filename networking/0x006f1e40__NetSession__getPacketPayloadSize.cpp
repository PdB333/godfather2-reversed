// FUNC_NAME: NetSession::getPacketPayloadSize
int __fastcall NetSession::getPacketPayloadSize(void* thisPtr) {
    // +0x04: packetSize (total packet size including header)
    int packetSize = *(int*)((char*)thisPtr + 4);

    // Check for special packet types: 0 (invalid) and 0x48 (72, possibly a keepalive or control packet)
    if (packetSize != 0 && packetSize != 0x48) {
        // For normal packets, subtract the header size (0x28 = 40 bytes) to get payload size
        // Note: The decompiler shows a dead branch (return 0x20) that is unreachable due to prior checks
        return packetSize - 0x28;
    }

    // Special types have no payload
    return 0;
}
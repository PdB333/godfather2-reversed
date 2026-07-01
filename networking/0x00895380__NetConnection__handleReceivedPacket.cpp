// FUNC_NAME: NetConnection::handleReceivedPacket
void __thiscall NetConnection::handleReceivedPacket(int *packetData) {
    int packetType = *packetData;

    // Check if packet type matches expected local sequence or type (offset +0x18)
    if (packetType == *(int *)((char *)this + 0x18)) {
        ((void (*)())(**(int **)((char *)this - 0x3c) + 0x1c / 4))();
        return;
    }

    // Check if packet type matches another local field (offset +0x20)
    if (packetType == *(int *)((char *)this + 0x20)) {
        ((void (*)())(**(int **)((char *)this - 0x3c) + 0x20 / 4))();
        return;
    }

    // Handle a global packet type (e.g., PACKET_TYPE_RELIABLE_ACK? or similar)
    if (packetType == DAT_0112e31c) {
        ((void (*)(int))(**(int **)((char *)this - 0x3c) + 0x2c / 4))(packetData[1]);
        FUN_00408a00(0); // likely resets some state or logs
        return;
    }

    // Handle another global packet type (e.g., PACKET_TYPE_BANDWIDTH_UPDATE)
    if (packetType == DAT_01218048) {
        // Check if a global flag is set and a condition holds
        if (*(int *)(DAT_0112b9b4 + 0x40) != 0 && FUN_00481620() != '\0') {
            int multiplier = 1;
            // If the packet data's sub-field matches a local field (offset +0x14)
            if (*(int *)(packetData[1] + 8) == *(int *)((char *)this + 0x14)) {
                multiplier = ((int (*)(int))(**(int **)((char *)this - 0x3c) + 0x2c / 4))(*(int *)(packetData[1] + 0x10));
            }
            // Multiply a value in the packet data (bandwidth or priority weight)
            *(int *)(packetData[1] + 0xC) *= multiplier;
        }
        return;
    }

    // No other packet types are handled here; function returns implicitly
}
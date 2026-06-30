// FUNC_NAME: TNLConnection::processReliablePacket
// Function address: 0x00633f00
// Role: Process incoming reliable packet and store payload into receive buffer

class TNLConnection {
public:
    // +0x08: pointer to packet data area (source for this function)
    uint32_t* mPacketData;
    // +0x1c: base sequence number for the reliable receive window
    int mReceiveBaseSeq;
    // +0x1c (also used as pointer to receive buffer array): 
    //   Actually, the decompiler shows the same offset for two different uses.
    //   Likely a miscompile; we treat mReceiveBaseSeq as int at +0x1c,
    //   and the buffer pointer is stored elsewhere (e.g., +0x20) but we preserve the code.
    uint32_t* mReceiveBuffer; // actually at +0x1c when cast to pointer?
};

int TNLConnection::processReliablePacket(int* packetHeaderA, int* packetHeaderB, int currentSequence) {
    // Current base sequence of the receive window
    int baseSeq = *(int*)((uintptr_t)this + 0x1c);

    // Global state (probably packet handler state or connection state)
    int* globalState = (int*)FUN_00637f90(); 

    // Packet headers: values 5 and 7 indicate reliable data or ack subtypes
    if ((*packetHeaderA != 5 && *packetHeaderA != 7) || (*globalState == 0)) {
        // Try alternative header interpretation
        if (*packetHeaderB != 5 && *packetHeaderB != 7) {
            return 0; // invalid header type
        }
        globalState = (int*)FUN_00637f90();
    }

    // The state must be 6 (active receiving mode)
    if (*globalState != 6) {
        return 0;
    }

    // Update the reliable receive window (acknowledge, slide, etc.)
    FUN_00633ac0((int)this, globalState, packetHeaderA, packetHeaderB);

    // Source data from the packet (8 bytes at +0x08)
    uint32_t* src = *(uint32_t**)((uintptr_t)this + 0x8);

    // Destination slot in the receive buffer (base pointer at +0x1c)
    uint32_t* dst = (uint32_t*)(*(int*)((uintptr_t)this + 0x1c) + (currentSequence - baseSeq));

    // Copy 8 bytes (two 32-bit values) into the slot
    *dst = *src;
    dst[1] = src[1];

    return 1;
}
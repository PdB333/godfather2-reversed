// FUNC_NAME: NetConnection::sendReliablePacket
// Address: 0x00564fd0
// Role: Sends a reliable packet, records sequence number for ACK tracking, and invokes a callback.
// Offsets: this-4 = base class pointer, this+0x128 = sequence array[64], this+0x228 = count, this+0x230 = onPacketSent callback.
// Note: The original decompiled output contained an ambiguous stack function pointer call. This reconstruction omits it as an artifact.

// External helpers (to be re-identified):
// FUN_00564de0 = getPacketWindow(base, packetDataOffset0x110)
// FUN_004d3bc0 = writePacketHeader(packet+8)
// FUN_005653d0 = generateSequenceNumber(base, &seqOut)

void __thiscall NetConnection::sendReliablePacket(void* thisPtr, void* packet)
{
    // Adjust for multiple inheritance base class at -4
    void* basePtr = reinterpret_cast<char*>(thisPtr) - 4;

    // Retrieve packet buffer from connection's window manager
    int* packetVtable = reinterpret_cast<int*>(FUN_00564de0(basePtr, reinterpret_cast<char*>(packet) + 0x110));

    // Call virtual function at vtable+8 (likely "sendPacket" or "write")
    (reinterpret_cast<void(*)(void*)>(packetVtable[2]))(packet);

    // Finalize packet header at offset +8
    FUN_004d3bc0(reinterpret_cast<char*>(packet) + 8);

    // Generate and store new sequence number
    uint32_t seqNum;
    FUN_005653d0(basePtr, &seqNum);

    // Invoke onPacketSent callback if present (offset +0x230)
    void (*onSent)(void*) = *reinterpret_cast<void(**)(void*)>(reinterpret_cast<char*>(thisPtr) + 0x230);
    if (onSent) {
        onSent(packet);
    }

    // Record sequence number for ACK tracking if buffer not full
    uint32_t* countPtr = reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(thisPtr) + 0x228);
    if (*countPtr < 64) {
        uint32_t* seqArray = reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(thisPtr) + 0x128);
        seqArray[*countPtr] = seqNum;
        (*countPtr)++;
    }
}
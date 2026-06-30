// FUN_00460210: PacketProcessor::processPacket
void PacketProcessor::processPacket(int packetHandle)
{
    if (this) {
        // Dereference vtable or function table pointer from object
        int* funcTable = *(int**)this; // this points to function table pointer
        int eventData[2]; // local buffer for event info
        eventData[0] = 0;
        int timestamp = getCurrentTime(); // FUN_004dafd0
        // Call function at vtable offset 0x98 (index 38) – likely onPacketReceived
        ((void (*)(int*, int))funcTable[0x98 / 4])(eventData, timestamp);
    }
    releasePacket(packetHandle); // FUN_004eacb0 – free packet resources
    flushNetworkOutput(); // FUN_004df4f0 – flush network buffers
}
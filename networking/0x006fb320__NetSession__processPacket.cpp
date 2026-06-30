// FUNC_NAME: NetSession::processPacket
int* __thiscall NetSession::processPacket(void* thisConnection, uint32_t packetHeader) {
    int* packetResult;
    uint8_t localBuffer[4]; // small scratch buffer
    int* localPacketPtr;
    uint32_t localState;

    // Get global instance pointer (e.g., GodfatherGameManager or TNLGlobalState)
    packetResult = (int*)FUN_0049c9c0(); // likely returns pointer to a global state structure

    // Check global structure at offset 0x84 for a sub-object
    if (*(int*)(DAT_0122337c + 0x84) == 0) {
        localState = 0;
    } else {
        // Read value from sub-object at offset 0x1c
        localState = *(uint32_t*)(*(int*)(DAT_0122337c + 0x84) + 0x1c);
    }

    localPacketPtr = packetResult;

    // If the connection has substantial data (>15 units) at offset 0x18,
    // copy a value from offset 0x10 and process a sub-packet
    if (*(uint32_t*)((char*)thisConnection + 0x18) > 0xf) {
        packetHeader = *(uint32_t*)((char*)thisConnection + 0x10); // overwrite parameter
        FUN_006fb160(localBuffer, &packetHeader); // process the header/buffer
    }

    // Parse or transform the packet result pointer
    FUN_006fb0f0(&localPacketPtr);

    // Check return code: 4 indicates a specific packet type (e.g., reliable packet)
    if (*packetResult == 4) {
        FUN_006f0310(); // handle that packet type (e.g., processReliablePacket)
        return packetResult;
    }

    return (int*)0x0;
}
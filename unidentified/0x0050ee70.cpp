// FUN_NAME: TNLConnection::buildAndSendCommandPacket
void TNLConnection::buildAndSendCommandPacket() {
    // Allocate memory for packet buffer (possibly resets internal state)
    allocatePacketMemory();

    // Set vtable pointer for this packet object (this is a constructor-like initialization)
    *reinterpret_cast<void**>(this) = &g_packetVTable; // PTR_FUN_00e380f8

    // Clear reliability counters at +0xA0 and +0xA4
    this->reliableSeqCounter = 0;    // +0x28 (0xA0)
    this->unreliableSeqCounter = 0;  // +0x29 (0xA4)

    // Global connection manager state at g_connectionManager+0xD
    if (*(char*)(g_connectionManager + 0xD) != '\0') {
        return; // Connection is being terminated, abort
    }

    // Check if connection is fully established
    bool connectionReady = isConnectionEstablished();
    if (!connectionReady) {
        *(char*)(g_connectionManager + 0xC) = 1; // Set pending connection flag
        return;
    }

    // Determine command type from this+0x5B
    uint8_t commandType = this->commandType; // +0x5B

    int dataPointer = 0;
    if (commandType == 1) {
        // Command type 1: Action data
        dataPointer = getActionData();
    } else if (commandType == 6) {
        // Command type 6: Mission check
        uint32_t* missionPtr = reinterpret_cast<uint32_t*>(this->missionObject); // in_EAX[9]
        if (!(missionPtr[0x104 / 4] & 0x400)) {
            this->missionData = 0; // +0x19
        } else {
            this->missionData = getMissionData(); // +0x19
        }
        goto afterDataRetrieval;
    } else if (commandType == 2) {
        // Command type 2: Event data
        dataPointer = getEventData();
    } else {
        goto afterDataRetrieval;
    }

    if (dataPointer != 0) {
        this->actionData = dataPointer; // +0x18
    }

afterDataRetrieval:
    // Prepare packet payload
    this->packetData1 = 0; // +0x1A
    this->packetData2 = 0; // +0x1B

    uint32_t sourceAddrLow = *(uint32_t*)(this->connectionObj + 0x10); // in_EAX[1]+0x10
    uint32_t sourceAddrHigh = this->destinationObj; // in_EAX[10]

    // Serialize command type and misc fields into header
    uint16_t fieldA = *reinterpret_cast<uint16_t*>(&this->fieldOffset17); // +0x17
    uint16_t fieldB = *reinterpret_cast<uint16_t*>(&this->fieldOffset16); // +0x16
    uint32_t headerDataLow, headerDataHigh;
    serializePacketHeader(&headerDataLow, &headerDataHigh, sourceAddrLow, fieldA, fieldB, commandType);

    // Transmit the fully assembled packet
    transmitPacket(this,
                   ((uint64_t)sourceAddrHigh << 32) | sourceAddrLow,
                   ((uint64_t)headerDataHigh << 32) | headerDataLow,
                   this->packetData1, // +0x1A
                   this->packetData2, // +0x1B
                   this->reliableQueue, // +0x4 (in_EAX[4])
                   this->unreliableQueue); // +0x5 (in_EAX[5])
}
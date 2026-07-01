// FUNC_NAME: NetConnection::sendPacket

#include <cstdint>

// Forward declarations of called functions (unknown real names)
void initPacketBuffer(char* buffer);
bool fillPacketData(uint64_t* dataPair, int* packetHeader, char* buffer, bool flag);
uint32_t computeChecksum();
void assemblePacket(uint64_t* dataPair, char* buffer, uint32_t packetType, uint32_t unknown, uint32_t* checksum, bool hasChecksum);
void getConnectionInfo(char* outBuffer, void*** table);
int* openResource(uint32_t resourceId);

// Global variables from decompiled output
extern uint32_t g_currentTimeMs; // DAT_01205224
extern void* g_someFunctionTable; // PTR_FUN_00e32a8c
extern uint32_t g_someConstant; // _DAT_00d5780c

// PacketHeader struct based on param_3 offsets
struct PacketHeader {
    int seqNum;        // [0]
    int flags;         // [0x1c] = 28
    int retryCount;    // [0x3b] = 59
    int id0;           // [2]
    int id1;           // [5]
    uint64_t dataPair; // [3] as uint64
    // plus more fields for fallback
};

// Connection data struct based on param_2 offsets
struct ConnectionData {
    uint8_t field_12;        // +0x12
    uint32_t lastSendTime;   // +0x20
    void* field_18;          // +0x18 (pointer to object with vtable at +8)
    int* field_8;            // +0x8 (handle?)
};

// Function body
bool NetConnection::sendPacket(PacketHeader* header, ConnectionData* connection, uint8_t flags) {
    bool success = true;
    int maxRetries = 1;
    int thisCopy = reinterpret_cast<int>(this); // for direct pointer arithmetic

    // Handle high priority flags: if flags has 0x10 and header conditions met, allow more retries
    if ((flags & 0x10) && (header->flags & 7) && (header->retryCount < 6)) {
        maxRetries = 3;
        connection->field_12 = 0; // reset some flag
    }

    // Loop while a slot is blocked (bit 4 set at offset *(this+0x24)+0x14 + header->seqNum*0x1c)
    while (*(reinterpret_cast<uint32_t*>(*(reinterpret_cast<int*>(thisCopy + 0x24) + 0x14 + header->seqNum * 0x1c)) & 4) != 0) {
        if (success) goto successLabel;

    retryCheck:
        // Check if enough time has passed (current time - last send <= 0x96)
        if (g_currentTimeMs <= connection->lastSendTime + 0x96) {
            return true; // not enough time, skip retry
        }
        if (connection->field_12 == 0) {
            return success; // if flag cleared, return current success state
        }
        maxRetries--;
        if (maxRetries < 1) {
            return success;
        }
        // else continue loop (slot may become free)
    }

    // Build packet buffer
    char packetBuffer[12];
    initPacketBuffer(packetBuffer);

    // Call optional callback from connection object
    void (**callback)(ConnectionData*, char*) = *(void (***)(ConnectionData*, char*))(*(reinterpret_cast<int*>(connection->field_18) + 8));
    if (callback) {
        (*callback)(connection, packetBuffer);
    }

    header->retryCount++; // increment retry attempt

    // Decide which data pair to use for the packet payload
    int someId;
    uint64_t dataPair;
    if (!(flags & 1) && (!(flags & 2) || ((*(reinterpret_cast<uint32_t*>(header->id0 + 0x8e0) >> 0x19) & 1) == 0))) {
        // Use direct data from header
        someId = header->id1;
        dataPair = *reinterpret_cast<uint64_t*>(&header->id0 + 3); // actually header[3] uint64
    } else {
        // Use fallback from a function call
        if (!fillPacketData(&dataPair, header + 0x29, packetBuffer, ~flags & 1)) {
            someId = header->id1; // wait, header[0x11] = 17
            dataPair = *reinterpret_cast<uint64_t*>(header + 0xf);
        }
    }

    uint32_t checksum = 0;
    if (flags & 8) {
        checksum = computeChecksum();
    }

    // Assemble the actual network packet
    assemblePacket(&dataPair, packetBuffer,
                   ((flags & 8) ? 0x3ff0 : 0) + 0x10 | 0x40122,
                   0x100001,
                   &checksum,
                   (flags & 8) != 0);

    // Verify connection handle via some resource system
    uint32_t handle1 = 0xffffffff;
    uint32_t handle2 = 0xffffffff;
    void** table = &g_someFunctionTable;
    int unknownStack = 0;
    uint32_t value1 = g_someConstant;
    uint32_t value2 = 0;
    uint32_t value3 = g_someConstant;
    char buffer[92];
    getConnectionInfo(buffer, &table);

    if (unknownStack != 0) {
        int handle = 0;
        if ((*reinterpret_cast<char*>(unknownStack + 0x10) + unknownStack != 0) &&
            (int* arr = openResource(0x2001), arr != nullptr)) {
            handle = arr[0];
        }
        int otherHandle = (connection->field_8 != nullptr) ? *connection->field_8 - 0x48 : 0;
        if (handle != otherHandle) {
            success = false;
            goto retryCheck;
        }
    }

    success = true;

successLabel:
    connection->lastSendTime = g_currentTimeMs;
    return success;
}
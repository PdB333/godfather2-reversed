// FUNC_NAME: NetConnection::parseMessage
// Address: 0x0074ad10
// Handles incoming network messages by type hash

#define CONCAT44(hi, lo) (((uint64_t)(hi) << 32) | (uint64_t)(lo))

// Forward declarations of callees
void handleAck(void* subObj);              // FUN_00755a10
void handleDataPacket(void* subObj);       // FUN_0075cd50
uint getConnectionState(void);             // FUN_0077dd80
void setFlag(int val);                     // FUN_00744610
char checkReady(void* subObj);             // FUN_00749eb0
void prepareCallback(int param);           // FUN_0074a210
uint getPacketID(void);                    // FUN_00800b60
void defaultMessageHandler(void* packet);  // FUN_0073e4d0

// Known hash constants
const uint MSG_ACK      = 0x1b2d5c51;
const uint MSG_CONNECT  = 0x3c52ffda;
const uint MSG_DATA     = 0x6862a74c;

void __thiscall NetConnection::parseMessage(void* thisPtr, void* packetBuffer) {
    // Core object at this+0x5c (e.g., underlying network layer)
    int* coreObj = *(int**)((uintptr_t)thisPtr + 0x5c);

    // Interpret packet as uint array for offset access (offsets in 4-byte units)
    uint* packet = (uint*)packetBuffer;

    // Get message type hash from first dword (usually a virtual function call)
    uint msgHash = (*(uint(**)(void))(*(uint*)packet))();

    if (msgHash == MSG_ACK) {
        handleAck((void*)((uintptr_t)thisPtr + 0x74));   // +0x74: sub-object (ack state)
        packet[0x16] |= 2;   // Set bit 1 at byte offset 0x58
        return;
    }

    if (msgHash == MSG_CONNECT) {
        // Copy connection state from this message source
        *(uint64_t*)(packet + 0x16) = *(uint64_t*)((uintptr_t)thisPtr + 0x74);
        packet[0x18] = *(uint32_t*)((uintptr_t)thisPtr + 0x7c);
        packet[0x1b] |= 8;   // Flag bit 3
        packet[0x15] = DAT_00d64388;   // Global, probably connection ID

        // Set up callback pointers in packet
        *(uint64_t*)(packet + 0x28) = CONCAT44(&LAB_00749f40, (uint32_t)thisPtr);
        *(uint64_t*)(packet + 0x2a) = 0;
        *(uint64_t*)(packet + 0x2c) = CONCAT44(0x00000000, 0x74a130);
        packet[0x1b] |= 4;   // Flag bit 2

        *(uint64_t*)(packet + 0x22) = CONCAT44(&LAB_0072d0f0, (uint32_t)coreObj);
        *(uint64_t*)(packet + 0x24) = 0;
        *(uint64_t*)(packet + 0x26) = CONCAT44(&LAB_0074a150, (uint32_t)uStack_10); // uninitialized stack variable
        return;
    }

    if (msgHash == MSG_DATA) {
        handleDataPacket((void*)((uintptr_t)thisPtr + 0x74));

        // Fill packet with multiple data fields (function pointers, offsets)
        *(uint64_t*)(packet + 0x1e) = CONCAT44(FUN_007347e0, (uint32_t)coreObj);
        *(uint64_t*)(packet + 0x20) = (uint64_t)uStack_14 << 32; // uninitialized
        *(uint64_t*)(packet + 0x22) = CONCAT44(&LAB_0073b090, (uint32_t)uStack_10);
        *(uint64_t*)(packet + 0x24) = CONCAT44(&LAB_0072d0f0, (uint32_t)coreObj);
        *(uint64_t*)(packet + 0x26) = (uint64_t)uStack_14 << 32;
        *(uint64_t*)(packet + 0x28) = CONCAT44(&LAB_0074a150, (uint32_t)uStack_10);

        uint switchVal = getConnectionState();
        if (switchVal == 2 || switchVal == 3) {
            // State-specific processing
            setFlag(~(*(uint8*)((uintptr_t)coreObj + 0x1b97) & 1));
            char isReady = checkReady((void*)((uintptr_t)thisPtr + 0x74));
            if (isReady) {
                packet[0x2a] |= 2;   // Set bit 1
            }
        }

        // More packet field assignments
        *(uint64_t*)(packet + 0x4d) = CONCAT44(&LAB_00749f40, (uint32_t)thisPtr);
        *(uint64_t*)(packet + 0x4f) = 0;
        *(uint64_t*)(packet + 0x51) = CONCAT44(0x00000000, 0x74a130);
        packet[0x2a] |= 0x1000000;   // Set bit 24

        int offset = 0;
        if (coreObj[0x931] != 0) {
            offset = coreObj[0x931] - 0x48;
        }
        prepareCallback(offset);
        packet[0x2b] = getPacketID();

        // Call virtual function on core object (vtable slot +0x270)
        (*(void(**)(void))(*(uint32_t*)coreObj + 0x270))();
        return;
    }

    // Unknown message type – pass to default handler
    defaultMessageHandler(packetBuffer);
}
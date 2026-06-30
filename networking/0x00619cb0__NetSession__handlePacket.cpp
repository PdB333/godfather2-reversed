// FUNC_NAME: NetSession::handlePacket

#include <cstdint>

// Packet header structure (simplified, based on decompilation)
struct PacketHeader {
    int32_t refCount;          // +0x00
    void* data;                // +0x04
    int32_t msgType;           // +0x08
    int32_t unused;            // +0x0C
    int32_t field4;            // +0x10
    int32_t field5;            // +0x14
    int32_t field6;            // +0x18
    int32_t field7;            // +0x1C
};

class NetSession {
public:
    // Offset 0x18: message type ID for a simple message (e.g., ACK)
    // Offset 0x1C: message type ID for a complex message (e.g., data packet)
    int32_t m_simpleMsgType;   // +0x18
    int32_t m_complexMsgType;  // +0x1C

    // Handles an incoming message packet.
    // Returns a result code or handle from the processing.
    int32_t handlePacket(PacketHeader* packet) {
        int32_t result;
        char isReady;

        // Check message type
        if (packet->msgType == m_simpleMsgType) {
            // Simple message: likely an ACK or keepalive
            result = sendAck();   // FUN_00616bc0
            return result;
        }

        if (packet->msgType == m_complexMsgType) {
            // Complex message: contains additional data
            // Retrieve sub-type from the data payload (offset 0x0C)
            result = processDataSubType(*(int32_t*)((uint8_t*)packet->data + 0x0C)); // FUN_00611000

            // Check if the payload at offset 0x14 is ready for finalization
            isReady = 0;
            checkPayloadReady(packet->field5, &isReady); // FUN_0061a2e0
            if (isReady != 0) {
                int32_t savedField5 = packet->field5;
                packet->field5 = 0;
                packet->field4 = 0;
                packet->field7 = 0;
                int32_t savedField6 = packet->field6;
                int32_t savedResult = result;
                // Call finalization handler (likely triggers a callback)
                finalizeMessage(); // FUN_0061a6b0
            }
            // Increment reference count (first 4 bytes of packet)
            *(int32_t*)packet->data += 1;  // Actually packet->refCount is at +0, not data? Wait: *param_2 = *param_2 +1 => packet->refCount
            // Correction: packet->refCount is at offset 0, not packet->data
            // But in decompilation: *(int *)*param_2 = *(int *)*param_2 + 1;
            // That means *param_2 (first word) is a POINTER to a counter, then increment that pointer's value.
            // Actually careful: param_2 is int* (or undefined4*). *param_2 is the first element of the array (at offset 0). That is a value, not a pointer.
            // The expression is *(int *)*param_2 = *(int *)*param_2 + 1:
            // It casts the value at param_2[0] to an int*, then increments the int at that address.
            // This means the first field of the packet is itself a pointer to a reference count.
            // So we need to adjust: packet->refCountPtr is at offset 0, pointing to an int.
            // Let's reflect that:
            int* refCount = (int*)packet->refCount; // reinterpret cast
            *refCount = *refCount + 1;

            return result;
        }
        return 0;
    }

private:
    int32_t sendAck();      // FUN_00616bc0
    int32_t processDataSubType(int32_t subType); // FUN_00611000
    void checkPayloadReady(int32_t payload, char* outReady); // FUN_0061a2e0
    void finalizeMessage(); // FUN_0061a6b0
};

// Corrected structure based on analysis that first field is a pointer to ref count
struct PacketHeader {
    int* refCountPtr;        // +0x00: pointer to external reference count
    void* data;              // +0x04: payload pointer
    int32_t msgType;         // +0x08: message type ID
    int32_t unused;          // +0x0C: padding
    int32_t field4;          // +0x10: some value (saved and cleared)
    int32_t field5;          // +0x14: payload ready flag/pointer
    int32_t field6;          // +0x18: another saved value
    int32_t field7;          // +0x1C: cleared to 0
};
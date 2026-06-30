// FUNC_NAME: NetObjectiveSender::writePacket
// Function address: 0x005ee610
// Role: Serializes an objective update into a network packet for sending.

#include <cstdint>

// Forward declarations for external functions (from EARS networking library)
namespace EARS {
    namespace Net {
        uint32_t createBitStream(void* obj, uint32_t param2, uint32_t param3, void* buffer); // FUN_00c9cbe0
        void beginWrite(uint32_t type, uint32_t value);                                     // FUN_00c9cd40 (1-arg variant)
        void writeField(uint32_t fieldType, void* fieldData);                               // FUN_00c9cd40 (2-arg variant)
        uint32_t computeChecksum();                                                         // FUN_00c9eb20
        void finalizePacket();                                                              // FUN_00c9eac0 / FUN_00c9eae0 (two variants)
        void* getPacketObject();                                                            // FUN_005e9d10
    }
}

class NetObjectiveSender {
public:
    // Returns true if objective was successfully written into the packet.
    // param_2: Objective ID (or pointer to objective data) to be included.
    bool writePacket(int objectiveId) {
        uint32_t result = 0;

        // Check if objectiveId is nonzero and if the objective data exists.
        // +0x580 likely points to an array/list of active objectives.
        if (objectiveId != 0 && *(uint32_t*)((uint8_t*)this + 0x580) != 0) {
            void* packet = EARS::Net::getPacketObject();
            if (packet != nullptr) {
                uint32_t objectiveData = *(uint32_t*)((uint8_t*)this + 0x580); // +0x580: pointer to objective data
                // Prepare local buffer for serialization fields.
                // The buffer is a structure containing both fixed and variable fields.
                struct MessageBuffer {
                    uint64_t field0;    // offset -0x4c
                    uint64_t field1;    // offset -0x44
                    uint32_t field2;    // offset -0x34
                    int32_t  objectiveId; // offset -0x2c (set to param_2)
                    uint32_t field4;    // offset -0x1c
                    uint32_t field5;    // offset -0x14
                };
                MessageBuffer msgBuf = {0, 0, 0, objectiveId, 0, 0};

                // Initialize the packet header with the objective data and buffer.
                // (3rd parameter 5 likely indicates message type or field ID)
                EARS::Net::createBitStream(
                    (void*)objectiveData,
                    *(uint32_t*)((uint8_t*)packet + 0x10), // +0x10: some offset in the packet object
                    5,
                    &msgBuf
                );

                // Begin writing the packet (type 1, value 0 – likely start of message)
                EARS::Net::beginWrite(1, 0);
                // Write the fields from the buffer (type 5, using the struct)
                EARS::Net::writeField(5, &msgBuf);

                // Compute checksum for the packet
                uint32_t checksum = EARS::Net::computeChecksum();
                // Store checksum at offset +0x20 in the packet object
                *(uint32_t*)((uint8_t*)packet + 0x20) = checksum;

                // Finalize the packet (e.g., compute length, encrypt, etc.)
                EARS::Net::finalizePacket();
                // Store 0 at offset +0x28 (maybe reserved or flags)
                *(uint32_t*)((uint8_t*)packet + 0x28) = msgBuf.field4; // field4 is 0
            }
            result = 1;
        }
        return result != 0;
    }
};
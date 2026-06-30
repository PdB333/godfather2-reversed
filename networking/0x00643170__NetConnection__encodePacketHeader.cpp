// FUNC_NAME: NetConnection::encodePacketHeader
// Function address: 0x00643170
// Purpose: Writes a reliable packet header (type 0xb) into the send buffer.
// Handles sequence numbers, ack fields, buffer size checks, and checksum/flags.

#include <cstdint>

// Forward declarations for helper functions (defined elsewhere in TNL/EARS)
void* getCurrentPacket(); // FUN_00642b00 - returns pointer to current packet structure
void resendPacket(int sequence); // FUN_00642d90 - queue or resend a packet
void finalizePacket(); // FUN_00642ec0 - finalize and possibly send the packet
const char* errorMessage(const char* msg); // FUN_00638b80 - display error (e.g., “function or expression too complex”)
uint32_t computeFlags(); // FUN_00642fc0 - compute packet flags/checksum (9-bit value)
void writeToBuffer(uint32_t header, void* dest); // FUN_006438e0 - write 32-bit header to destination

class NetConnection {
public:
    // Fields (offsets in bytes)
    int* sendBuffer;           // +0x00: pointer to the start of the send buffer
    int* currentPacket;        // +0x04: pointer to current packet being built
    int sequenceNumber;        // +0x08: outgoing sequence number
    int ackField1;             // +0x0C: ack state field 1
    int ackField2;             // +0x10: ack state field 2
    int* writePointer;         // +0x14: current write position in buffer (maybe offset)
    int packetCount;           // +0x24 (offset 36): number of packets sent (mod 256)
    int maxPacketAge;          // +0x34 (offset 52): maximum sequence age before resend

    // Method: encodes packet header for reliable packet (type 0xb)
    void __thiscall encodePacketHeader(int* ackPacket) {
        // Step 1: Get the current packet structure (returned in EAX)
        int* packet = (int*)getCurrentPacket();  // in_EAX

        // Step 2: If packet type is reliable (0xb) and ack fields match, skip resend check
        if (*packet == 0xb) {
            if (packet[3] == packet[4]) // ack fields identical?
                goto skipResend;
            if (maxPacketAge <= packet[1]) {  // current sequence too old?
                resendPacket(packet[1]);
                goto skipResend;
            }
        }
        // Step 3: Finalize any previous packet (flush)
        finalizePacket();

skipResend:
        // Step 4: If the current packet is reliable and its sequence is within acceptable range,
        //         decrement the packet count (to allow reuse?).
        if ((*packet == 0xb) && (maxPacketAge <= packet[1]) && (packet[1] < 250)) {
            packetCount--;
        }

        // Step 5: Access the send buffer pointer and check capacity
        int* buffer = sendBuffer;  // iVar4 = *this (offset 0)
        int currentSize = packetCount;
        int requiredSize = currentSize + 2;
        // Buffer header byte at +0x47 holds max allowed size? (size field in buffer structure)
        uint8_t* bufferHeader = (uint8_t*)buffer + 0x47;
        if (*bufferHeader < requiredSize) {
            if (requiredSize > 0xF9) {
                // Buffer overflow: update sendBuffer pointer and report error
                buffer = (int*)writePointer;  // fallback to write pointer
                errorMessage("function or expression too complex");
                // extraout_ECX is ignored here (likely side effect)
            }
            *bufferHeader = (uint8_t)requiredSize;
        }

        // Step 6: Advance the packet count by 2 (header size?)
        packetCount += 2;  // param_1[9] += 2

        // Step 7: Compute flags/checksum for the packet
        uint32_t flags = computeFlags();  // uVar3 (9 bits)

        // Step 8: Build combined 32-bit header:
        //   bits 24-31: old packetCount (8 bits)
        //   bits 15-23: packet sequence (9 bits from packet[1])
        //   bits 6-14: flags (9 bits)
        //   bits 0-5: type (0xb = 11)
        uint32_t header = ((currentSize << 9 | packet[1]) << 9 | flags) << 6 | 0xb;
        // Equivalent: (currentSize<<24) | (packet[1]<<15) | (flags<<6) | 0xb

        // Step 9: Write header to buffer at writePointer + 8
        writeToBuffer(header, (void*)((uint8_t*)writePointer + 8));

        // Step 10: Handle ack packet (second argument) – adjust count if needed
        if ((*ackPacket == 0xb) && (maxPacketAge <= ackPacket[1]) && (ackPacket[1] < 250)) {
            packetCount--;
        }

        // Step 11: Update the current packet structure:
        //   sequence = old packetCount (the one before increment?)
        packet[1] = currentSize;
        //   type = 0xb (reliable)
        *packet = 0xb;

        return;
    }
};
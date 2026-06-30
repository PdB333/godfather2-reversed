// FUNC_NAME: NetConnection::buildGamePacketHeader
#include <cstdint>

// Input packet header structure (source)
struct InputPacketHeader {
    uint16_t type;    // 0 or 1 (unreliable/reliable?)
    uint16_t seq;     // sequence number
    uint32_t id;      // some identifier (e.g., message or object ID)
};

// Output packet header structure (16 bytes)
struct OutputPacketHeader {
    uint16_t type;      // always 2
    uint16_t seq;       // in network byte order
    uint32_t id;        // in network byte order
    uint8_t padding[8]; // zeroed (second half)
};

/**
 * Constructs a network packet header.
 * ESI points to output buffer, EDI points to input structure.
 * @param outSize receives total packet size (0x10)
 */
void buildGamePacketHeader(OutputPacketHeader* output, const InputPacketHeader* input, int32_t* outSize)
{
    if (input->type == 0 || input->type == 1) {
        // Clear the output buffer (16 bytes)
        output->type = 0;
        output->seq = 0;
        output->id = 0;
        // Second half is zeroed via pointer arithmetic
        *(uint64_t*)( (uint8_t*)output + 8 ) = 0;

        // Build the header in network order
        output->type = 2;
        output->seq = htons(input->seq);
        output->id = htonl(input->id);

        *outSize = 16;
    }
}
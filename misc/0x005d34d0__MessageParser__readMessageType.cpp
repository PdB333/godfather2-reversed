// FUNC_NAME: MessageParser::readMessageType
// Address: 0x005D34D0
// Role: Parses a 4-byte message type from a buffer after skipping 8 bytes,
// then determines a result code based on the message type and a versioning table.
// Results are stored in an external structure at offset 0xBC.

#include <cstdint>

// External globals from the binary (likely in .data or .bss)
extern uint32_t DAT_012058a4;              // Version index or flag
extern uint8_t  DAT_011a0f28[];            // Array of structures (size 0x38 each)

int __fastcall MessageParser::readMessageType(int* thisPtr)
{
    // Advance buffer offset by 8 (skip 8-byte header/padding)
    thisPtr[4] += 8;

    uint32_t versionIndex = DAT_012058a4;
    int currentOffset = thisPtr[4];                         // +0x10: current read offset
    uint8_t* buffer = reinterpret_cast<uint8_t*>(thisPtr[0]); // +0x00: buffer base

    // Read 4-byte little-endian message type from buffer at current offset
    int messageType =
        buffer[currentOffset] |
        (buffer[currentOffset + 1] << 8) |
        (buffer[currentOffset + 2] << 16) |
        (buffer[currentOffset + 3] << 24);

    // Advance offset by 4 after reading
    thisPtr[4] = currentOffset + 4;

    int resultCode = 0;
    uint8_t* tableEntry = nullptr;

    // If versionIndex is within valid range, locate the corresponding entry in the descriptor table
    if (versionIndex < 0x1000) {
        tableEntry = &DAT_011a0f28[versionIndex * 0x38]; // each descriptor is 0x38 bytes
    }

    if (tableEntry != nullptr) {
        uint16_t descriptorVersion = *reinterpret_cast<uint16_t*>(tableEntry + 2); // +0x02 in descriptor

        if (descriptorVersion < 0x281) {
            // Legacy handling: message types 1 and 2 both map to result code 1
            if (messageType == 1 || messageType == 2) {
                resultCode = 1;
            }
        } else {
            // Newer version: only message type 1 gets immediate result, others fall through
            if (messageType == 1) {
                *reinterpret_cast<int*>(thisPtr[7] + 0xBC) = 1; // +0x1C: output struct base, +0xBC result field
                return 1;
            }
        }
    }

    // Message type 3 always yields result code 2
    if (messageType == 3) {
        resultCode = 2;
    }

    // Store the final result code into the external struct
    *reinterpret_cast<int*>(thisPtr[7] + 0xBC) = resultCode;

    // Return value: low byte set to 1, upper 24 bits copied from messageType (bits 8-31)
    return (messageType & 0xFFFFFF00) | 1;
}
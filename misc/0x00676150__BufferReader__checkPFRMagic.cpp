// FUNC_NAME: BufferReader::checkPFRMagic
// Function at 0x00676150
// Checks if a "PFR" magic (3 bytes) exists at a given start offset in a buffer.
// Reads 4 bytes but only checks first 3 for 'P','F','R'.
// Temporarily advances offset by 10 after reading, then restores to start offset.

#include <cstdint>

struct BufferReader {
    char* buffer;      // +0x00: base address of raw data
    int32_t offset;    // +0x04: current read position
    // +0x08: unknown padding/field (index 2)
    int32_t startOffset; // +0x0C: initial offset to check (index 3)
};

bool __fastcall checkPFRMagic(BufferReader* thisPtr) {
    int32_t originalStart = thisPtr->startOffset;  // iVar1 = param_1[3]
    thisPtr->offset = originalStart;               // param_1[1] = iVar1

    // Read 4 bytes from (buffer + originalStart)
    uint32_t raw = *reinterpret_cast<uint32_t*>(thisPtr->buffer + originalStart);

    // Extract first three bytes
    char b0 = static_cast<char>(raw & 0xFF);
    char b1 = static_cast<char>((raw >> 8) & 0xFF);
    char b2 = static_cast<char>((raw >> 16) & 0xFF);

    // Advance offset by 10 (possibly skip header metadata)
    thisPtr->offset = originalStart + 10;

    if (b0 == 'P' && b1 == 'F' && b2 == 'R') {
        // Magic found -> reset offset to start and return true
        thisPtr->offset = originalStart;
        return true;
    } else {
        // Magic not found -> reset offset to start and return false
        thisPtr->offset = originalStart;
        return false;
    }
}
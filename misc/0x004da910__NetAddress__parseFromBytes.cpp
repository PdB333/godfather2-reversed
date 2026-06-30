// FUNC_NAME: NetAddress::parseFromBytes
#include <cstdint>

// Structure:
// +0x00: uint8 type
// +0x01: char name[8] (copied from packet bytes 8..15)
// +0x0C: uint32 addressPart1 (28 bits)
// +0x10: uint32 addressPart2 (28 bits)
// +0x14: int errorHandler (pointer to error callback, can be 0)
// Total size: 0x18 (24 bytes)

// Magic packet identifiers used in EARS network layer
static const uint32 MAGIC0 = 0xBADBADBA;
static const uint32 MAGIC1 = 0xBEEFBEEF;
static const uint32 MAGIC2 = 0xEAC15A55;
static const uint32 MAGIC3 = 0x91100911;

void __thiscall NetAddress::parseFromBytes(uint32 *inputData) {
    // this points to a NetAddress object (in unaff_ESI)
    int *this_addr = reinterpret_cast<int *>(this); // for field access
    this_addr[5] = 0; // +0x14 = 0, init error handler pointer

    // Check for magic packet (first 4 uint32)
    if (inputData[0] == MAGIC0 && inputData[1] == MAGIC1 &&
        inputData[2] == MAGIC2 && inputData[3] == MAGIC3) {
        this_addr[5] = 0;   // redundant
        *this_addr = 1;     // type = 1 (magic success)
        return;
    }

    // Normal packet: set type to 0x58 (pending decode error?)
    *this_addr = 0x58;

    // Copy bytes 8..15 (inputData[2] and inputData[3] as bytes) into name field
    // Validate each byte <= 0x7F (ASCII printable range)
    byte *nameDest = reinterpret_cast<byte *>(this_addr + 1); // +0x01
    byte *src = reinterpret_cast<byte *>(inputData);
    for (uint32 i = 0; i < 8; i++) {
        byte b = src[8 + i];   // bytes 8..15 of input data
        if (b > 0x7F) {
            goto error_handling;
        }
        nameDest[i] = b;
    }

    // Check first byte of input (high byte of inputData[0]) against 127.0.0.1
    // i.e., only accept addresses with first octet < 127
    if ((inputData[0] & 0xFF000000) < 0x7F000001) {
        // Append extra bytes from input (byte 3) and null-terminate?
        nameDest[8] = src[3];   // +0x09 = byte 3 of inputData[0]
        nameDest[9] = 0x00;     // null terminator

        // Extract two 28-bit values from first 2 uint32
        this_addr[4] = inputData[1] & 0x0FFFFFFF;                    // +0x10
        this_addr[3] = ((inputData[0] & 0x00FFFFFF) << 4) | (inputData[1] >> 28); // +0x0C
        return;
    }

    // Fall through to error handling
error_handling:
    int errorHandler = this_addr[5]; // +0x14
    *this_addr = 1;                 // type = 1 (error)
    if (errorHandler != 0) {
        // Check if error handler has its own callback
        if (*(int *)(errorHandler + 0x14) != 0) {
            FUN_004d8c70(1); // unknown logging/cleanup
        }
        FUN_009c8eb0(errorHandler); // release/delete callback object
    }
    this_addr[5] = 0; // clear error handler
    return;
}
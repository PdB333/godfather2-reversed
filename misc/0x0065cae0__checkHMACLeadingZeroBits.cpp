// FUNC_NAME: checkHMACLeadingZeroBits
// Address: 0x0065cae0
// Computes a HMAC (or similar) using key (in EAX), two 8-byte data blocks, and checks if the first numBits bits of the hash are zero.
// Returns: 0 if leading bits are all zero (unknown encoding, see caller FUN_0065cc60).
// Uses internal hash functions: hashInit (0x006595c0), hashUpdate (0x00659640), hashFinal (0x00659730).

#include <cstdint>

uint32_t checkHMACLeadingZeroBits(uint32_t key, uint32_t data1, uint32_t data2, uint32_t numBits) {
    // Convert key to big-endian byte array (4 bytes)
    uint8_t keyBytes[4];
    keyBytes[0] = (key >> 24) & 0xFF;
    keyBytes[1] = (key >> 16) & 0xFF;
    keyBytes[2] = (key >> 8) & 0xFF;
    keyBytes[3] = key & 0xFF;

    uint8_t hashCtx[208]; // hash context structure, initialized by hashInit
    hashInit(hashCtx);

    // Update hash with key (size 8? possibly 4, but decompiler shows 8)
    hashUpdate(hashCtx, keyBytes, 8);
    // Update hash with first data block (8 bytes)
    hashUpdate(hashCtx, reinterpret_cast<const uint8_t*>(data1), 8);
    // Update hash with second data block (8 bytes)
    hashUpdate(hashCtx, reinterpret_cast<const uint8_t*>(data2), 8);

    uint8_t hashOutput[32]; // final hash output
    hashFinal(hashCtx, hashOutput);

    uint32_t byteIndex = 0;
    // Check full 8‑bit chunks while at least 8 bits remain
    while (numBits > 8) {
        if (hashOutput[byteIndex] != 0) {
            // Return encoded position of first non‑zero byte
            return byteIndex & 0xffffff00;
        }
        numBits -= 8;
        byteIndex++;
    }

    // Check the remaining < 8 bits in the final byte
    uint32_t mask = -1 << (8 - numBits); // 32‑bit mask with low (8-numBits) bits zero
    uint32_t condition = (mask & hashOutput[byteIndex]) != 0;
    uint32_t lowByte = 0x01 - condition; // 0 if non‑zero, 1 if all zero
    uint32_t highPart = byteIndex >> 8;   // likely 0 for typical hash sizes
    // CONCAT31(highPart, lowByte) – assume it packs highPart as three bytes and lowByte as the final byte
    return (highPart << 8) | lowByte;
}
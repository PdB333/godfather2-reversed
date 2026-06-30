// FUNC_NAME: hashKeyToBucketIndex
// Computes a bucket index from a 32-bit key using two precomputed tables.
// g_byteTable[256] and g_intTable[256] are initialized elsewhere.
// The result is clamped to the range [g_byteTable[0], g_byteTable[1])? Actually
// if sum >= g_byteTable[1] then returns g_byteTable[0] (likely an empty sentinel).

#include <cstdint>

extern uint8_t g_byteTable[256];   // +0x00f17680 (byte lookup table)
extern int32_t g_intTable[256];    // +0x00f17684 (int lookup table, but offset may differ)

uint32_t __fastcall hashKeyToBucketIndex(uint32_t key)
{
    uint32_t sum = g_byteTable[(key >> 16) & 0xFF]
                 + g_byteTable[(key >> 8) & 0xFF]
                 + g_byteTable[key >> 24]
                 + g_intTable[key & 0xFF];

    if (g_byteTable[1] < sum) {
        sum = g_byteTable[0];
    }
    return sum;
}
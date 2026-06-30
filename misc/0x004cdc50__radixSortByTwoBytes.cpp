// FUNC_NAME: radixSortByTwoBytes

#include <cstdint>
#include <emmintrin.h> // for _mm_clflush

// Global count arrays for radix sort (256 shorts each)
static short g_countLow[256] = {0};
static short g_countHigh[256] = {0};

// Sorts an array of 4-byte records by the first two bytes (byte0 = LSB, byte1 = MSB)
// using a two-pass counting radix sort (first pass by byte0, second pass by byte1).
// The input buffer is sorted in-place; param_3 is a temporary buffer of the same size.
// param_1 : number of records
// param_2 : pointer to input array (4 bytes per record)
// param_3 : pointer to temporary buffer (same size)
void radixSortByTwoBytes(uint32_t count, void* input, void* temp)
{
    // Zero out count arrays (0x80 dwords = 512 bytes = 256 shorts)
    uint32_t* pCountLow = reinterpret_cast<uint32_t*>(g_countLow);
    for (int i = 0; i < 0x80; ++i) {
        *pCountLow++ = 0;
    }
    uint32_t* pCountHigh = reinterpret_cast<uint32_t*>(g_countHigh);
    for (int i = 0; i < 0x80; ++i) {
        *pCountHigh++ = 0;
    }

    // First pass: count occurrences of each byte0 value
    if (count != 0) {
        uint8_t* pb = reinterpret_cast<uint8_t*>(input) + 2; // skip first 2 bytes of first record? Actually input+2 points to byte1 of first record? Wait, starting offset 2 means byte1 of first record? Let's carefully examine.
        // In the original code: pbVar5 = (byte *)(param_2 + 2);
        // That is byte * starting at input+2. Then *pbVar5 is byte at input+2 (second byte of first record?), and pbVar5[1] is byte at input+3 (third byte). That would be bytes at offsets 2 and 3, not 0 and 1. But then the increment pbVar5 += 4 moves to next record, so each record is 4 bytes. So the two bytes used are the last two bytes of each record? Actually offset 0 and 1 are first two bytes; offset 2 and 3 are bytes 2 and 3. So the sort key is bytes at offsets 2 and 3, not first two. Wait: The first loop:
        //   bVar1 = pbVar5[1];   // byte at offset 3 of record (since pbVar5 points to record+2)
        //   (&DAT_01223580)[*pbVar5]  // byte at offset 2 of record
        //   (&DAT_01223780)[bVar1]   // byte at offset 3
        // So it's using byte at offset 2 as index for low count, byte at offset 3 as index for high count.
        // Then later the sorting passes also use those offsets: first pass reads byte at offset 2 from input, copies entire 4-byte record to temp. Second pass reads byte at offset 3 from temp, copies back to input.
        // So the sort key is the two bytes at offsets 2 and 3 of each 4-byte record (the high two bytes if 32-bit). That is a 16-bit value at offset 2.
        // This is unusual; typical sorting by a 32-bit key would use bytes 0 and 1. But we follow the original.
        uint32_t idx0, idx1;
        for (uint32_t i = 0; i < count; ++i) {
            uint8_t* record = reinterpret_cast<uint8_t*>(input) + i * 4;
            idx0 = record[2]; // byte0 of key (offset 2)
            idx1 = record[3]; // byte1 of key (offset 3)
            g_countLow[idx0]++;
            g_countHigh[idx1]++;
        }
    }

    // Convert counts to cumulative sums (prefix sum)
    short sumLow = 1;
    short sumHigh = 1;
    for (uint32_t i = 0; i < 256; ++i) {
        short origLow = g_countLow[i];
        g_countLow[i] = sumLow - 1;
        sumLow += origLow;

        short origHigh = g_countHigh[i];
        g_countHigh[i] = sumHigh - 1;
        sumHigh += origHigh;
    }

    // First pass: distribute records from input to temp based on byte0 (offset 2)
    if (count != 0) {
        for (uint32_t i = 0; i < count; ++i) {
            uint8_t* record = reinterpret_cast<uint8_t*>(input) + i * 4;
            uint32_t key = record[2];
            uint32_t dest = g_countLow[key];
            g_countLow[key] = dest + 1;
            // copy 4 bytes
            reinterpret_cast<uint32_t*>(temp)[dest] = reinterpret_cast<uint32_t*>(input)[i];
        }
    }

    // Second pass: distribute records from temp back to input based on byte1 (offset 3)
    if (count != 0) {
        for (uint32_t i = 0; i < count; ++i) {
            uint8_t* recInTemp = reinterpret_cast<uint8_t*>(temp) + i * 4;
            uint32_t key = recInTemp[3]; // byte1 of key (offset 3)
            uint32_t dest = g_countHigh[key];
            g_countHigh[key] = dest + 1;
            // copy 4 bytes
            reinterpret_cast<uint32_t*>(input)[dest] = reinterpret_cast<uint32_t*>(temp)[i];
        }
    }

    // Flush cache lines of count arrays (for cache coherency)
    for (uint32_t offset = 0; offset < sizeof(g_countLow); offset += 64) {
        _mm_clflush(reinterpret_cast<char*>(g_countLow) + offset);
        _mm_clflush(reinterpret_cast<char*>(g_countHigh) + offset);
    }
}
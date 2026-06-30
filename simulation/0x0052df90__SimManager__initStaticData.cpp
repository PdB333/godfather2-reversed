// FUNC_NAME: SimManager::initStaticData
// Function address: 0x0052df90
// Role: Initializes the static singleton instance of SimManager, zeroing slot arrays and setting up default values.
// The static data is at address 0x01219388 and contains 32 slots of 24 bytes each, followed by status and copy arrays.

#include <cstdint>

// The static data structure (size approximately 0x480 + 32 bytes)
// Internally organized as:
//   uint8_t slotData[32][24];   // offset 0x000
//   int32_t  slotStatus[32];    // offset 0x300 (initialized to -1)
//   int32_t  slotCopy[32];      // offset 0x380 (copy of slotData[?][3])
//   uint8_t  slotFlags[32];     // offset 0x480
// plus two separate bytes at 0x01219858 and 0x01219859

extern uint8_t g_simManagerData[0x500]; // approximate size, actual size unknown

uint8_t* SimManager::initStaticData()
{
    uint8_t* base = &g_simManagerData[0x00]; // address 0x01219388

    // Zero the first part of slot data (from offset 0x08? Actually starting at 0x01219390, which is base+8)
    // This loop zeroes 32 blocks of 24 bytes each.
    uint8_t* p = base + 0x08; // 0x01219390
    for (int32_t i = 0; i < 32; i++)
    {
        *(uint32_t*)(p - 8) = 0;      // offset -8 from p (i.e., base+0)
        *(uint32_t*)(p - 4) = 0;      // offset -4
        *(uint32_t*)(p + 0) = 0;      // offset 0
        *(uint32_t*)(p + 4) = 0;      // offset 4
        *(uint32_t*)(p + 8) = 0;      // offset 8
        *(uint32_t*)(p + 12) = 0;     // offset 12
        p += 24;
    }

    // Zero two specific bytes
    *(base + 0x4D0) = 0; // DAT_01219858 = base+0x4D0
    *(base + 0x4D1) = 0; // DAT_01219859 = base+0x4D1

    // Second loop: zero the main slot area starting from base, and set slotStatus to -1
    p = base;
    uint32_t offset = 0x300; // start of slotStatus array within base
    do {
        *(uint64_t*)p = 0;          // 8 bytes
        *(uint64_t*)(p + 8) = 0;    // next 8 bytes
        *(uint64_t*)(p + 16) = 0;   // next 8 bytes (total 24)
        // Set slotStatus element to -1 (0xFFFFFFFF)
        *(uint32_t*)(base + offset) = 0xFFFFFFFF;
        offset += 4;
        p += 24;
    } while (offset < 0x380); // runs 32 times (0x300..0x37C)

    // Third loop: zero extra area and copy selected data, also zero slotFlags
    uint32_t* src = (uint32_t*)(base + 0x14); // 0x0121939c, points to the 4th int of each 24-byte block
    offset = 0x400; // start of slotCopy area
    int32_t idx = 0;
    do {
        // Zero at base - 0x80 + offset (i.e., &DAT_01219308 + offset)
        // That area is before the main base, but it's zeroed here.
        *(uint32_t*)(base - 0x80 + offset) = 0;
        // Copy from source (which walks through slotData's 4th ints) to slotCopy area
        *(uint32_t*)(base + offset) = *src;
        // Zero slotFlags array (at base + 0x480)
        *(base + 0x480 + idx) = 0;
        offset += 4;
        idx++;
        src += 6; // advance by 24 bytes (6*4)
    } while (offset < 0x480); // runs 32 times

    // Zero additional fields (apparently not part of arrays)
    *(uint32_t*)(base + 0x4A0) = 0; // DAT_01219828
    *(uint32_t*)(base + 0x4A8) = 0; // DAT_01219830
    *(uint32_t*)(base + 0x4B0) = 0; // _DAT_01219838
    *(uint32_t*)(base + 0x4B8) = 0; // _DAT_01219840
    *(uint32_t*)(base + 0x4C0) = 0; // _DAT_01219848
    *(uint32_t*)(base + 0x4C8) = 0; // _DAT_01219850
    *(uint32_t*)(base + 0x4A4) = 0; // DAT_0121982c
    *(uint32_t*)(base + 0x4AC) = 0; // DAT_01219834
    *(uint32_t*)(base + 0x4B4) = 0; // _DAT_0121983c
    *(uint32_t*)(base + 0x4BC) = 0; // _DAT_01219844
    *(uint32_t*)(base + 0x4C4) = 0; // _DAT_0121984c
    *(uint32_t*)(base + 0x4CC) = 0; // _DAT_01219854

    // Return pointer to the static singleton
    return base;
}
// FUNC_NAME: initGlobalConstants
// Function address: 0x0085bf70
// Role: Initializes a global array of 15 uint32_t constants (likely CRC32 table or hash seeds)
// Called from: 0x0085c150 (initialization routine)

#include <cstdint>

// Global array at 0x0112dee4, 15 elements, 4 bytes each
uint32_t g_globalConstants[15];

void initGlobalConstants()
{
    // +0x00
    g_globalConstants[0] = 0x72d75ddd;
    // +0x04
    g_globalConstants[1] = 0xe8b44e0b;
    // +0x08
    g_globalConstants[2] = 0xa0dd1995;
    // +0x0C
    g_globalConstants[3] = 0x926a34e7;
    // +0x10
    g_globalConstants[4] = 0x24a64fdc;
    // +0x14
    g_globalConstants[5] = 0x54c9a756;
    // +0x18
    g_globalConstants[6] = 0xd378ba0f;
    // +0x1C
    g_globalConstants[7] = 0x094bf238;
    // +0x20
    g_globalConstants[8] = 0x8e0025cb;
    // +0x24
    g_globalConstants[9] = 0x248ac107;
    // +0x28
    g_globalConstants[10] = 0x77130eac;
    // +0x2C
    g_globalConstants[11] = 0x81d43daf;
    // +0x30
    g_globalConstants[12] = 0x932488ce;
    // +0x34
    g_globalConstants[13] = 0x2fc3226e;
    // +0x38
    g_globalConstants[14] = 0x94cf70a7;
}
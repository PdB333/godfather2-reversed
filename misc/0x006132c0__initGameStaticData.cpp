// FUNC_NAME: initGameStaticData
// Function address: 0x006132c0
// Role: Initialize global static data block at 0x011f69b0 (size 0xa90) with default values and call subsystem initializers.

#include <cstring>

// Externals defined elsewhere
extern const int g_sentinelValue; // DAT_00e2b1a4 - likely invalid/empty value
extern int g_globalInitFlag;       // DAT_011f7430 - per-frame initialization flag

// Subsystem initialization functions
void initNetworkOrInputSubsystem(); // FUN_006142d0
void initAudioOrPhysicsSubsystem(); // FUN_00614910

void initGameStaticData() {
    // Zero out the entire global data block
    memset(reinterpret_cast<void*>(0x011f69b0), 0, 0xa90);

    // Interpret the data block as an array of 32-bit integers (size 0xa90/4 = 676 ints)
    int* data = reinterpret_cast<int*>(0x011f69b0);

    // Initialize specific fields; pattern suggests list of 48 "slots" plus two extra entries at offset 0x200
    data[0]  = g_sentinelValue; // +0x00
    data[1]  = 0;                // +0x04
    data[2]  = 0;                // +0x08
    data[3]  = 0;                // +0x0C
    data[4]  = 0;                // +0x10
    data[5]  = g_sentinelValue; // +0x14
    data[6]  = 0;                // +0x18
    data[7]  = 0;                // +0x1C
    data[8]  = 0;                // +0x20
    data[9]  = 0;                // +0x24
    data[10] = g_sentinelValue; // +0x28
    data[11] = 0;                // +0x2C
    data[12] = 0;                // +0x30
    data[13] = 0;                // +0x34
    data[14] = 0;                // +0x38
    data[15] = g_sentinelValue; // +0x3C
    data[16] = g_sentinelValue; // +0x40
    data[17] = 0;                // +0x44
    data[18] = 0;                // +0x48
    data[19] = 0;                // +0x4C
    data[20] = 0;                // +0x50
    data[21] = g_sentinelValue; // +0x54
    data[22] = 0;                // +0x58
    data[23] = 0;                // +0x5C
    data[24] = 0;                // +0x60
    data[25] = 0;                // +0x64
    data[26] = g_sentinelValue; // +0x68
    data[27] = 0;                // +0x6C
    data[28] = 0;                // +0x70
    data[29] = 0;                // +0x74
    data[30] = 0;                // +0x78
    data[31] = g_sentinelValue; // +0x7C
    data[32] = g_sentinelValue; // +0x80
    data[33] = 0;                // +0x84
    data[34] = 0;                // +0x88
    data[35] = 0;                // +0x8C
    data[36] = 0;                // +0x90
    data[37] = g_sentinelValue; // +0x94
    data[38] = 0;                // +0x98
    data[39] = 0;                // +0x9C
    data[40] = 0;                // +0xA0
    data[41] = 0;                // +0xA4
    data[42] = g_sentinelValue; // +0xA8
    data[43] = 0;                // +0xAC
    data[44] = 0;                // +0xB0
    data[45] = 0;                // +0xB4
    data[46] = 0;                // +0xB8
    data[47] = g_sentinelValue; // +0xBC

    // Additional entries at offset 0x200 (0x80 ints from base)
    data[0x200 / 4] = 0;                 // +0x200
    data[0x200 / 4 + 1] = g_sentinelValue; // +0x204

    // Initialize subsystems
    initNetworkOrInputSubsystem();
    initAudioOrPhysicsSubsystem();

    // Ensure subsystem B is initialized even if flag wasn't set
    if ((g_globalInitFlag & 1) == 0) {
        initAudioOrPhysicsSubsystem();
    }
    g_globalInitFlag |= 1;
}
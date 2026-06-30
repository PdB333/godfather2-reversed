// FUNC_NAME: GlobalStats::recordMaximum
// Address: 0x004e4860
// Records maximum values and associated data from two float4 vectors and two floats.
// Called with __fastcall convention: ECX unused, EAX = flags, stack: vecA*, vecB*, valX, valY.
// Global structure at 0x011251f0 stores accumulated stats.

#include <cstdint>

// Constants
extern int32_t gCounterIncrement; // DAT_00e2b1a4

// Forward declaration of reset function
void resetGlobalStats(float valX, float valY, int32_t resetMode); // FUN_005263c0

// Global stats structure (offset 0x011251f0, size 0x30)
struct GlobalStats {
    uint32_t flags;       // +0x00 (0x011251f0)
    float maxX;           // +0x04 (0x011251f4)
    float maxY;           // +0x08 (0x011251f8)
    float arrayA[4];      // +0x0C (0x01125200)
    float arrayB[4];      // +0x1C (0x01125210)
    int32_t counter;      // +0x2C (0x01125220)
};

extern GlobalStats gGlobalStats;

// __fastcall: ECX = unused (param_1), EAX = flags, EDX = vecA, stack: vecB, valX, valY
void __fastcall GlobalStats::recordMaximum(
    void* ecx,                     // unused
    uint32_t flags,                // in EAX
    float* vecA,                   // in EDX
    float* vecB,                   // [esp+0]
    float valX,                    // [esp+4]
    float valY)                    // [esp+8]
{
    // If flag bit 0 is set, reset stats instead of recording max
    if (flags & 1) {
        resetGlobalStats(valX, valY, 0);
        return;
    }

    // Update maximum values
    if (gGlobalStats.maxX < valX) {
        gGlobalStats.maxX = valX;
    }
    if (gGlobalStats.maxY < valY) {
        gGlobalStats.maxY = valY;
    }

    // Store associated vectors
    gGlobalStats.arrayA[0] = vecA[0];
    gGlobalStats.arrayA[1] = vecA[1];
    gGlobalStats.arrayA[2] = vecA[2];
    gGlobalStats.arrayA[3] = vecA[3];

    gGlobalStats.arrayB[0] = vecB[0];
    gGlobalStats.arrayB[1] = vecB[1];
    gGlobalStats.arrayB[2] = vecB[2];
    gGlobalStats.arrayB[3] = vecB[3];

    // Accumulate flags
    gGlobalStats.flags |= flags;

    // Increment counter
    gGlobalStats.counter += gCounterIncrement;
}
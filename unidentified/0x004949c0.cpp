// FUN_004949c0: TimerSystem::initHighResTimer

#include <windows.h>

// Timer slot structure (0x18 bytes each)
struct TimerSlot {
    uint32_t startLow;   // +0x00 // Low part of start QPC
    uint32_t startHigh;  // +0x04 // High part of start QPC
    uint32_t deltaLow;   // +0x08 // Low part of delta (accumulated?)
    uint32_t deltaHigh;  // +0x0C // High part of delta
    uint8_t  unused;     // +0x10 // Padding or flag
    // +0x11..0x17 padding
};

// Global timer state
static uint32_t* g_timerSlots = (uint32_t*)0x0110a580;  // PTR_DAT_0110a580
static uint32_t g_freqLow  = 0;   // DAT_01163ec0
static uint32_t g_freqHigh = 0;   // DAT_01163ec4
static float    g_invFreq  = 0.0f; // _DAT_01163dac
static float    g_tickTime = 0.0f; // _DAT_01163da8
static float    g_scale1   = 0.0f; // _DAT_01163ecc
static float    g_scale2   = 0.0f; // _DAT_01163ed0
static float    g_scale3   = 0.0f; // _DAT_01163ec8

// Forward declaration for unknown time getter
uint64_t FUN_00494ad0(void); // Likely returns current QPC as a 64-bit value

void TimerSystem::initHighResTimer(void)
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER currentCount;
    uint32_t* slotBase = g_timerSlots;
    int offset;

    // Get QPC frequency
    QueryPerformanceFrequency(&frequency);
    g_freqLow  = frequency.LowPart;
    g_freqHigh = frequency.HighPart;

    // Initialize first two DWORDs of global structure to 0 (unused)
    slotBase[0] = 0;
    slotBase[1] = 0;

    // Compute 1.0 / frequency (absolute value) as float
    // Note: original uses a sign-extended 64-bit absolute value
    LARGE_INTEGER absFreq;
    absFreq.HighPart = frequency.HighPart & 0x7FFFFFFF;
    absFreq.LowPart  = frequency.LowPart;
    g_invFreq = 1.0f / (float)(absFreq.QuadPart);

    // Precomputed scaling factors
    g_tickTime = g_invFreq * *(float*)0x00e44638; // DAT_00e44638
    g_scale1   = (float)(*(double*)0x00e2e230) * g_invFreq; // DAT_00e2e230
    g_scale2   = g_invFreq * *(float*)0x00e44794; // DAT_00e44794
    g_scale3   = g_invFreq;

    // Store scaling factor in stack (unused later? just to keep a copy)
    // LStack_10._0_4_ = g_invFreq;

    // Get first timestamp
    QueryPerformanceCounter(&currentCount);
    slotBase[2] = currentCount.LowPart;  // +0x08
    slotBase[3] = currentCount.HighPart; // +0x0C
    slotBase[4] = currentCount.LowPart;  // +0x10 (duplicate? likely reset delta)
    slotBase[5] = currentCount.HighPart; // +0x14

    // Initialize 5 timer slots (0x18 bytes each, spaced by 0x18)
    offset = 0;
    do {
        // Clear the byte at slot start + 0x20 (relative to base)
        *(uint8_t*)(slotBase + offset + 0x20) = 0;

        // Get current QPC (64-bit)
        uint64_t qpc = FUN_00494ad0();

        // Store at offset +0x18 (8 bytes)
        *(uint64_t*)((uint8_t*)slotBase + offset + 0x18) = qpc;

        // Also store low 32 bits at offset +0x10
        *(uint32_t*)((uint8_t*)slotBase + offset + 0x10) = (uint32_t)qpc;

        // Copy high 32 bits from offset +0x1C to +0x14
        *(uint32_t*)((uint8_t*)slotBase + offset + 0x14) = *(uint32_t*)((uint8_t*)slotBase + offset + 0x1C);

        offset += 0x18;
    } while (offset < 0x78); // 5 iterations (0x78/0x18 = 5)
}
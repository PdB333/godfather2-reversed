// 0x0040df60
// Frame timing wrapper around the main engine tick.
//
// The global state block at DAT_01223380 looks like a singleton performance
// monitor. This function brackets the core engine update with
// QueryPerformanceCounter snapshots and increments per-phase counters so the
// engine can measure how often the tick path runs and how long it takes.

#include <Windows.h>

#include <cstdint>

struct FrameTimingState
{
    std::uint8_t reserved_00[0x9C];  // 0x00 - 0x9B
    std::uint32_t preTickCount;      // 0x9C
    std::uint32_t postTickCount;     // 0xA0
    std::uint8_t reserved_A4[4];     // 0xA4 - 0xA7
    std::uint32_t preTickQpcLow;     // 0xA8
    std::int32_t preTickQpcHigh;     // 0xAC
    std::uint32_t postTickQpcLow;    // 0xB0
    std::int32_t postTickQpcHigh;    // 0xB4
};

extern "C" {
    // Main engine tick/update routine called between the two timing samples.
    extern void FUN_0060d8b0(char shouldAdvance);

    // Singleton timing/statistics object used by this wrapper.
    extern FrameTimingState* g_FrameTimingState;  // DAT_01223380
}

void __cdecl UpdateFrameTimingAndDispatch(bool shouldAdvance)
{
    FrameTimingState* timing = g_FrameTimingState;

    if (timing != nullptr)
    {
        // Snapshot the high-resolution timer before the core tick runs.
        ++timing->preTickCount;

        LARGE_INTEGER qpcBefore{};
        QueryPerformanceCounter(&qpcBefore);
        timing->preTickQpcLow = static_cast<std::uint32_t>(qpcBefore.LowPart);
        timing->preTickQpcHigh = static_cast<std::int32_t>(qpcBefore.HighPart);
    }

    // The flag is forwarded as a byte-sized boolean to the engine's main
    // update routine. In the original binary, this is the work performed
    // between the two performance-counter samples.
    FUN_0060d8b0(static_cast<char>(shouldAdvance ? 1 : 0));

    if (timing != nullptr)
    {
        // Snapshot the high-resolution timer after the core tick completes.
        ++timing->postTickCount;

        LARGE_INTEGER qpcAfter{};
        QueryPerformanceCounter(&qpcAfter);
        timing->postTickQpcLow = static_cast<std::uint32_t>(qpcAfter.LowPart);
        timing->postTickQpcHigh = static_cast<std::int32_t>(qpcAfter.HighPart);
    }
}

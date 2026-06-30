// Reconstructed from Ghidra export at 0x0040eac0.
//
// This routine walks a 32-bit mask, one bit at a time, and increments a matching
// counter slot for every set bit. Whenever it touches at least one slot, it also
// marks the global "dirty" flag so the rest of the game can observe that the
// counters have been updated.

#include <cstdint>

extern "C" {
    // Ghidra labels:
    //   DAT_01205260 .. DAT_012052df -> 32 signed 32-bit counters
    //   DAT_01205258                 -> update/dirty flag
    extern std::int32_t g_bitUsageCounters[32];
    extern std::int32_t g_bitUsageCountersDirty;
}

// Processes the bits in `mask` from least-significant to most-significant.
// Each set bit increments the corresponding counter entry.
extern "C" void FUN_0040eac0(std::uint32_t mask) {
    std::int32_t* counter = g_bitUsageCounters;

    for (std::uint32_t bitIndex = 0; bitIndex < 32; ++bitIndex, ++counter, mask >>= 1) {
        if ((mask & 1u) != 0) {
            ++(*counter);
            g_bitUsageCountersDirty = 1;
        }
    }
}

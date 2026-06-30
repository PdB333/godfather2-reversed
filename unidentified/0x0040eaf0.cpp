// Reconstructed from Ghidra export: 0x0040eaf0
// Original behavior:
//   - decrement up to 32 tracked counters using a packed 4-bit-per-group mask
//   - recompute the total number of outstanding references
//   - if nothing is left pending and no external hold flags remain, advance the
//     subsystem into state 2

#include <cstdint>

extern "C" {
    // DAT_01205258 in the original binary.
    // This subsystem state is updated by the nearby helper functions:
    //   1 = active / busy
    //   2 = idle / ready
    //   3 = alternate mode used by the transition code
    extern std::uint32_t gSubsystemState_01205258;

    // DAT_0120525c in the original binary.
    // Bitmask of external holds. As long as any bit remains set, the subsystem
    // must not transition to state 2 even if all per-slot counters are zero.
    extern std::uint32_t gPendingHoldMask_0120525c;

    // DAT_01205260 .. DAT_012052dc in the original binary.
    // 32 tracked counters laid out consecutively in memory.
    extern std::int32_t gTrackedSlotRefCounts_01205260[32];
}

static inline void DecrementIfNonZero(std::int32_t& value)
{
    if (value != 0) {
        --value;
    }
}

// Ghidra: FUN_0040eaf0
void ReleasePackedSlotReferences(std::uint32_t packedMask)
{
    // Each nibble in packedMask controls one group of four counters:
    //   bit 0 -> slot 0
    //   bit 1 -> slot 1
    //   bit 2 -> slot 2
    //   bit 3 -> slot 3
    // Then the mask shifts right by four bits and the next group is processed.
    for (int groupIndex = 0; groupIndex < 8; ++groupIndex) {
        const std::uint32_t nibble = packedMask & 0xFu;
        const int baseIndex = groupIndex * 4;

        if ((nibble & 0x1u) != 0u) {
            DecrementIfNonZero(gTrackedSlotRefCounts_01205260[baseIndex + 0]);
        }
        if ((nibble & 0x2u) != 0u) {
            DecrementIfNonZero(gTrackedSlotRefCounts_01205260[baseIndex + 1]);
        }
        if ((nibble & 0x4u) != 0u) {
            DecrementIfNonZero(gTrackedSlotRefCounts_01205260[baseIndex + 2]);
        }
        if ((nibble & 0x8u) != 0u) {
            DecrementIfNonZero(gTrackedSlotRefCounts_01205260[baseIndex + 3]);
        }

        packedMask >>= 4;
    }

    // The original function performs a full sum over all 32 counters rather
    // than checking only the modified subset. Preserve that exact behavior.
    std::int32_t totalOutstandingRefs = 0;
    for (int i = 0; i < 32; ++i) {
        totalOutstandingRefs += gTrackedSlotRefCounts_01205260[i];
    }

    // Once all tracked references are gone and no external hold mask remains,
    // the subsystem moves to state 2. Nearby code treats this as the "ready"
    // state and applies the corresponding configuration.
    if (totalOutstandingRefs == 0 && gPendingHoldMask_0120525c == 0) {
        gSubsystemState_01205258 = 2;
    }
}

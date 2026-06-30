// Reconstructed from Ghidra export: 0x0040e5a0
// Tiny runtime flag setter. The related transition code at 0x0040e1f0 reads
// this byte to decide whether a scene/object promotion should be deferred.

#include <cstdint>

extern "C" {
    // Inferred global gate byte used during engine state transitions.
    extern std::uint8_t g_deferSceneObjectPromotion;
}

extern "C" void SetSceneObjectPromotionDeferred(std::uint8_t value)
{
    g_deferSceneObjectPromotion = value;
}

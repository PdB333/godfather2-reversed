// FUNC_NAME: ComputeBlockAdjustment
// Address: 0x005daa10
// Role: Compute a pointer adjustment based on a block size of 0x28 (40 bytes).
// The function takes an input value (param1), masks the low byte, calls a helper,
// and returns an adjusted pointer using register values that are set by the helper.
// Assumes int in_EAX and int unaff_EDI are provided by the caller context.

#include <cstdint>

// Forward declaration of the helper function (address 0x005daaa0)
extern void SomeHelper(uint32_t a, uint32_t b, int c, uint32_t d);

int __cdecl ComputeBlockAdjustment(uint32_t param1)
{
    uint32_t original = param1;
    uint32_t masked = param1 & 0xFFFFFF00; // Mask off low byte (e.g., lane index)

    // Call helper with original and masked values; third argument is 0
    SomeHelper(original, masked, 0, masked);

    // Compute block-aligned offset from unaff_EDI (base pointer) using
    // the difference between in_EAX (result from helper) and original.
    // 0x28 = 40, likely size of a block/struct.
    int diff = (int)(in_EAX - (int)original);
    int blockOffset = (diff / 0x28) * -0x28; // Round down to previous multiple of 0x28
    return unaff_EDI + blockOffset;
}
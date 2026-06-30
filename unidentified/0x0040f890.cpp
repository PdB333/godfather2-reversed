// Reconstructed function from The Godfather 2 (EA EARS engine)
// Address: 0x0040f890
//
// Purpose:
// Walk the active input/controller slot table and return the first slot whose
// descriptor type matches the selector value that the original binary carried
// in a register (Ghidra showed it as unaff_EDI).
//
// If no slot matches, the function returns 0x12, which is the engine's
// sentinel for "no valid slot selected".

#include <cstdint>

// Known external helpers from the input/controller registry.
// The names are retained from the Ghidra export set to keep the linkage clear.
extern "C" std::uint32_t FUN_00b92e50(void);
extern "C" std::uint32_t FUN_00b92e60(void);
extern "C" std::uint32_t FUN_00b94a20(std::uint32_t slotIndex);
extern "C" std::uint32_t FUN_00b94a40(std::uint32_t slotIndex);

struct ControllerSlotDescriptor
{
    std::uint32_t reserved_00; // Unknown data at +0x00.
    std::int32_t type;         // +0x04, compared against the selector.
};

constexpr std::uint8_t kInvalidControllerSlot = 0x12;

// This is reconstructed as a free helper because the decompiler lost the
// original register-based selector argument. The binary logic is equivalent to:
// "find the first slot whose descriptor->type equals desiredDescriptorType".
std::uint8_t FindControllerSlotByDescriptorType(std::int32_t desiredDescriptorType)
{
    const std::uint32_t registryHandle = FUN_00b92e50();
    if (registryHandle == 0) {
        return kInvalidControllerSlot;
    }

    const std::uint32_t slotCount = FUN_00b92e60();
    if (slotCount == 0) {
        return kInvalidControllerSlot;
    }

    for (std::uint32_t slotIndex = 0; slotIndex < slotCount; ++slotIndex) {
        // The original function performs this lookup even though the value is
        // unused. Keep it here to preserve the exact control flow and any
        // possible side effects in the underlying engine helpers.
        (void)FUN_00b94a40(slotIndex);

        const auto* descriptor = reinterpret_cast<const ControllerSlotDescriptor*>(
            FUN_00b94a20(slotIndex)
        );

        if (descriptor != nullptr && descriptor->type == desiredDescriptorType) {
            return static_cast<std::uint8_t>(slotIndex);
        }
    }

    return kInvalidControllerSlot;
}


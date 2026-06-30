// Reconstructed from Ghidra export: 0x0040f300
// EARS::Framework::InputDeviceManager bootstrap / constructor body.
//
// This routine installs the runtime vtables, clears the per-slot controller
// state, creates the optional owned message-context helper when the caller
// does not provide one, and registers the message IDs used by controller
// connect/disconnect and input-focus notifications.

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace EARS::Framework
{
    class InputDeviceManager
    {
    public:
        InputDeviceManager* __thiscall InitializeRuntimeState(std::uint32_t messageContextOrHandle);
    };
}

namespace
{
    template <typename T>
    static T& At(void* self, std::size_t offset)
    {
        return *reinterpret_cast<T*>(static_cast<std::uint8_t*>(self) + offset);
    }

    static constexpr std::size_t kSlotCount = 16;
    static constexpr std::size_t kSlotStride = 0x44;
    static constexpr std::size_t kSlotPresenceOffset = 0x6a;

    using SlotStateCallback = void(__cdecl *)(std::uint32_t slotIndex, int isConnected, std::uint32_t slotId, int reserved);

    static std::uint32_t HashMessageName(const char* messageName)
    {
        // The retail binary hashes ASCII message names with a case-folded
        // multiply-add loop using 0x1003f as the multiplier.
        std::uint32_t hash = 0;

        for (const unsigned char* cursor = reinterpret_cast<const unsigned char*>(messageName); *cursor != 0; ++cursor)
        {
            std::uint8_t ch = *cursor;
            if (ch >= 'A' && ch <= 'Z')
            {
                ch = static_cast<std::uint8_t>(ch + 0x20);
            }

            hash = hash * 0x1003f + ch;
        }

        return hash;
    }

    static void RetainSharedMessageRegistration(
        std::uint32_t* messageSlot,
        std::uint32_t& refCount,
        std::uint16_t fallbackFlags)
    {
        if (*messageSlot == 0)
        {
            return;
        }

        // The engine keeps a separate reference-counted record for each
        // registered message. If that record is missing, the code falls back to
        // a direct unregister / re-register style update.
        refCount += 1;

        const std::uint32_t registrationRecord = FUN_00407da0();
        if (registrationRecord == 0)
        {
            FUN_004084d0(messageSlot, fallbackFlags);
            return;
        }

        auto* const flags = reinterpret_cast<std::uint16_t*>(registrationRecord + 0x14);
        const std::uint16_t currentFlags = *flags;

        // Ghidra recovered an odd flag-twiddle here. Keep the exact behavior so
        // the recovered control flow matches the retail binary.
        *flags =
            (((static_cast<std::uint16_t>((currentFlags * 2U) >> 1) + 1U) ^ currentFlags) & 0x7fffU) ^
            currentFlags;
    }
}

extern "C"
{
    extern void* PTR_FUN_00e2f480;
    extern void* PTR_LAB_00e2f490;
    extern void* PTR_LAB_00e2f494;

    extern EARS::Framework::InputDeviceManager* DAT_012233b4;
    extern std::uint32_t DAT_012069d4;
    extern std::uint32_t DAT_012069d8;
    extern std::uint32_t DAT_012069ec;
    extern std::uint32_t DAT_012069f0;
    extern std::uint32_t DAT_012069fc;
    extern std::uint32_t DAT_01206a00;
    extern std::uint32_t DAT_01206a08;
    extern std::uint32_t DAT_01206a10;
    extern std::uint32_t DAT_01206a14;
    extern std::uint32_t DAT_01206a18;

    std::uint32_t FUN_009c8e50(std::uint32_t size);
    std::uint32_t FUN_004b4d10(std::uint32_t* contextBootstrap);
    std::uint32_t FUN_00407da0();
    void FUN_00408260(std::uint32_t* messageSlot, std::uint32_t messageId);
    void FUN_004084d0(std::uint32_t* messageSlot, std::uint16_t flags);
    void FUN_00b92eb0(std::uint32_t messageHandle);
    void FUN_00b95f70(void* packet);
    void FUN_00b92e50();
    void FUN_00b95be0();
    std::uint32_t FUN_00b92e60();
    std::uint32_t FUN_00b94a40(std::uint32_t slotIndex);
    void FUN_004105f0(EARS::Framework::InputDeviceManager* self, std::uint8_t slotIndex);
    void FUN_00408a00(std::uint32_t* packet, char dispatchFlag);
}

// Ghidra: FUN_0040f300
EARS::Framework::InputDeviceManager* __thiscall
EARS::Framework::InputDeviceManager::InitializeRuntimeState(std::uint32_t messageContextOrHandle)
{
    auto* const self = this;
    auto* const base = reinterpret_cast<std::uint8_t*>(self);

    // Initial object state. The first vtable swap is the transient base-class
    // state; the final vtable write below becomes the runtime-facing type.
    At<void**>(self, 0x00) = &PTR_FUN_00e2f480;
    At<std::uint32_t>(self, 0x04) = 1;
    At<std::uint32_t>(self, 0x08) = 0;
    At<void**>(self, 0x0C) = &PTR_LAB_00e2f494;
    At<std::uint32_t>(self, 0x10) = 0;
    At<std::uint32_t>(self, 0x14) = 1;
    At<std::uint16_t>(self, 0x18) = 0;
    At<std::uint64_t>(self, 0x1a) = 0;
    At<std::uint64_t>(self, 0x22) = 0;
    At<std::uint8_t>(self, 0x2a) = 0;
    At<std::uint8_t>(self, 0x2b) = 0;

    // Publish the singleton early so the later bootstrap helpers can find the
    // manager while the rest of the constructor is still running.
    DAT_012233b4 = self;

    // Store the caller-supplied message context or helper pointer. If the
    // caller passes 0, the constructor allocates and wraps a default helper.
    At<std::uint32_t>(self, 0x4e4) = messageContextOrHandle;
    At<void**>(self, 0x0C) = &PTR_LAB_00e2f490;
    At<std::uint8_t>(self, 0x4e8) = 0;
    At<std::uint8_t>(self, 0x52c) = 0;

    // Clear the 16 controller state blocks. Each slot uses a 0x44-byte block
    // starting at 0x2c, with the per-slot presence flag at +0x6a.
    std::memset(base + 0x2c, 0, 0x440);
    for (std::size_t slotIndex = 0; slotIndex < kSlotCount; ++slotIndex)
    {
        base[kSlotPresenceOffset + slotIndex * kSlotStride] = 0;
    }

    // Reset the main controller-selection and routing fields to a clean
    // startup state.
    for (std::size_t offset = 0x540; offset <= 0x560; offset += 4)
    {
        At<std::uint32_t>(self, offset) = 0;
    }
    std::memset(base + 0x564, 0x12, 5);
    std::memset(base + 0x52d, 0, 8);
    std::memset(base + 0x535, 0, 8);

    At<std::uint8_t>(self, 0x53d) = 0x0f;
    At<std::uint8_t>(self, 0x574) = 0;
    At<std::uint32_t>(self, 0x578) = 0x20;
    At<std::uint32_t>(self, 0x57c) = 0x80;
    At<std::uint32_t>(self, 0x580) = 0;
    At<std::uint32_t>(self, 0x584) = 0;
    At<std::uint32_t>(self, 0x588) = 0;

    // Global callback hook used by the slot bootstrap path.
    At<std::uint32_t>(self, 0x49c) = 0;

    if (At<std::uint32_t>(self, 0x4e4) == 0)
    {
        // The constructor can synthesize a small auxiliary context object when
        // the caller does not provide one.
        std::uint32_t contextBootstrap[3]{};
        contextBootstrap[0] = 2;
        contextBootstrap[1] = 8;

        std::uint32_t* messageHelper = nullptr;
        if (FUN_009c8e50(0x48) != 0)
        {
            messageHelper = reinterpret_cast<std::uint32_t*>(FUN_004b4d10(contextBootstrap));
            if (messageHelper != nullptr)
            {
                messageHelper = messageHelper + 1;
            }
        }

        At<std::uint32_t>(self, 0x4e4) = reinterpret_cast<std::uint32_t>(messageHelper);
        At<std::uint8_t>(self, 0x4e8) = 1;
    }

    // Reinitialize the shared message-context registry and its scratch packet.
    FUN_00b92eb0(At<std::uint32_t>(self, 0x4e4));
    {
        std::uint8_t bootstrapPacket[8]{};
        bootstrapPacket[4] = 1;
        FUN_00b95f70(bootstrapPacket);
    }
    FUN_00b92e50();
    FUN_00b95be0();

    // Reset the per-slot runtime object table before repopulating it from the
    // live controller registry.
    std::memset(base + 0x4ec, 0, 0x40);

    const std::uint32_t slotCount = FUN_00b92e60();
    if (slotCount != 0)
    {
        for (std::uint32_t slotIndex = 0; slotIndex != slotCount; ++slotIndex)
        {
            const std::uint32_t slotState = FUN_00b94a40(slotIndex);
            if (*reinterpret_cast<std::int32_t*>(slotState + 4) != 1)
            {
                continue;
            }

            if (slotIndex < kSlotCount)
            {
                // Mirror the active controller state into the local slot
                // table and build the runtime helper for the slot.
                base[kSlotPresenceOffset + slotIndex * kSlotStride] = 1;
                FUN_004105f0(self, static_cast<std::uint8_t>(slotIndex));

                std::uint32_t connectPacket[3]{};
                connectPacket[0] = DAT_012069fc;
                connectPacket[1] = slotIndex;
                FUN_00408a00(connectPacket, 0);
            }

            const std::uint32_t slotCallback = At<std::uint32_t>(self, 0x49c);
            if (slotCallback != 0)
            {
                reinterpret_cast<SlotStateCallback>(static_cast<std::uintptr_t>(slotCallback))(
                    slotIndex,
                    1,
                    slotIndex,
                    0);
            }
        }
    }

    // Controller connect/disconnect and window-focus messages.
    FUN_00408260(&DAT_012069fc, HashMessageName("iMsgControllerConnect"));
    if (DAT_012069fc != 0)
    {
        RetainSharedMessageRegistration(&DAT_012069fc, DAT_01206a00, 0x8000);
    }

    FUN_00408260(&DAT_01206a10, HashMessageName("iMsgControllerDisconnect"));
    if (DAT_01206a10 != 0)
    {
        RetainSharedMessageRegistration(&DAT_01206a10, DAT_01206a14, 0x8000);
    }

    FUN_00408260(&DAT_01206a08, HashMessageName("iMsgWindowHasLostInputFocus"));
    FUN_00408260(&DAT_01206a18, HashMessageName("iMsgWindowHasGainedInputFocus"));

    return self;
}

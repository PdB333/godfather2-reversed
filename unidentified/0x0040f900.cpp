// Reconstructed from Ghidra export: 0x0040f900
// EARS::Framework::InputDeviceManager helper used by the window-focus / input
// routing path.
//
// The function resolves the currently active controller slot, tells the global
// slot registry which slot is active, then forwards a small mode packet to the
// slot runtime through three virtual calls:
//   - vtable+0x20: begin / prepare
//   - vtable+0x34: dispatch the context + mode pair
//   - vtable+0x1c: end / commit

#include <cstddef>
#include <cstdint>

namespace EARS::Framework {

class InputDeviceManager
{
public:
    void __thiscall DispatchActiveControllerPacket(std::uint32_t routingHint, std::uint32_t modeCode);
};

} // namespace EARS::Framework

namespace
{
    template <typename T>
    static T& At(void* self, std::size_t offset)
    {
        return *reinterpret_cast<T*>(static_cast<std::uint8_t*>(self) + offset);
    }

    struct SlotRuntime
    {
        void** vtable;
    };

    using BeginDispatchFn = void(__thiscall *)(SlotRuntime*);
    using DispatchPacketFn = void(__thiscall *)(SlotRuntime*, std::uint32_t, std::uint32_t);
    using EndDispatchFn = void(__thiscall *)(SlotRuntime*);

    static constexpr std::size_t kBeginOffset = 0x20;
    static constexpr std::size_t kDispatchOffset = 0x34;
    static constexpr std::size_t kEndOffset = 0x1c;
}

extern "C" {
    extern std::uint8_t FUN_0040f890(void);
    extern void FUN_00b92e50(std::uint32_t slotIndex);
    extern void* FUN_00b94a80(std::uint32_t slotIndex);
}

// Ghidra: FUN_0040f900
void __thiscall EARS::Framework::InputDeviceManager::DispatchActiveControllerPacket(
    std::uint32_t routingHint,
    std::uint32_t modeCode)
{
    // The visible call sites pass a routing value, but the recovered body uses
    // the manager's internal active-slot selector instead.
    (void)routingHint;

    const std::uint8_t slotIndex = FUN_0040f890();
    FUN_00b92e50(slotIndex);

    SlotRuntime* const runtimeObject = static_cast<SlotRuntime*>(FUN_00b94a80(slotIndex));
    if (runtimeObject == nullptr) {
        return;
    }

    void** const vtable = runtimeObject->vtable;

    // Begin the slot runtime transaction.
    reinterpret_cast<BeginDispatchFn>(vtable[kBeginOffset / sizeof(void*)])(runtimeObject);

    // Forward the manager's cached window / focus context together with the
    // caller-supplied mode code.
    reinterpret_cast<DispatchPacketFn>(vtable[kDispatchOffset / sizeof(void*)])(
        runtimeObject,
        At<std::uint32_t>(this, 0x540),
        modeCode);

    // Close the transaction so the runtime can commit any state changes.
    reinterpret_cast<EndDispatchFn>(vtable[kEndOffset / sizeof(void*)])(runtimeObject);
}

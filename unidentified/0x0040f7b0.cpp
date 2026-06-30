// Reconstructed from Ghidra export: 0x0040f7b0
// EARS::Framework::InputDeviceManager non-deleting destructor body.
//
// The scalar-deleting wrapper at 0x0040f790 invokes this routine before it
// optionally frees the object. The teardown restores the object's inactive
// state, releases the 16 owned slot objects, drops the owned message/context
// handle, and unregisters the cached controller / focus message ids.

#include <cstddef>
#include <cstdint>

namespace EARS::Framework {

class InputDeviceManager
{
public:
    void __thiscall DestroyRuntimeState();
};

} // namespace EARS::Framework

namespace
{
    template <typename T>
    static T& At(void* self, std::size_t offset)
    {
        return *reinterpret_cast<T*>(static_cast<std::uint8_t*>(self) + offset);
    }

    using SlotCleanupFn = void(__thiscall*)(void*, int);
    using ContextReleaseFn = void(__thiscall*)(void*);
}

extern "C" {
    extern void* PTR_FUN_00e2f480;
    extern void* PTR_LAB_00e2f494;

    extern void FUN_00b96040();
    extern void FUN_00408310(std::uint32_t* messageSlot);
    extern void FUN_004086d0(std::uint32_t* messageSlot);
    extern void FUN_004083d0();

    // Cached engine message / registration handles.
    extern std::uint32_t DAT_012069d4;
    extern std::uint32_t DAT_012069ec;
    extern std::uint32_t DAT_012069fc;
    extern std::uint32_t DAT_01206a08;
    extern std::uint32_t DAT_01206a10;
    extern std::uint32_t DAT_01206a18;
    extern std::uint32_t DAT_012233b4;
}

void __thiscall EARS::Framework::InputDeviceManager::DestroyRuntimeState()
{
    auto* const self = this;

    // Restore the manager to its inactive state before any owned objects are
    // released. The constructor flips these fields once initialization is done.
    At<void**>(self, 0x00) = &PTR_FUN_00e2f480;
    At<void**>(self, 0x0C) = &PTR_LAB_00e2f494;

    // Release the 16 slot helpers owned by this manager. Each slot stores a
    // polymorphic object; its first virtual method is invoked with destroy flag
    // 1, then the pointer is cleared.
    for (std::uint32_t slotIndex = 0; slotIndex < 16; ++slotIndex) {
        void*& slot = At<void*>(self, 0x4ec + slotIndex * sizeof(void*));
        if (slot != nullptr) {
            void* const slotObject = slot;
            void** const slotVtable = *reinterpret_cast<void***>(slotObject);
            auto const release = reinterpret_cast<SlotCleanupFn>(slotVtable[0]);
            release(slotObject, 1);
            slot = nullptr;
        }
    }

    // Engine-global flush / synchronization step used by the surrounding
    // message system before the cached registrations are dropped.
    FUN_00b96040();

    // When this instance owns the auxiliary context object, release it through
    // the virtual method at vtable+0xC. The original code subtracts 4 bytes
    // before dispatching and assumes the stored pointer is valid.
    if (At<std::uint8_t>(self, 0x4e8) != '\0') {
        void* context = At<void*>(self, 0x4e4);
        context = static_cast<void*>(static_cast<std::uint8_t*>(context) - 4);

        void** const contextVtable = *reinterpret_cast<void***>(context);
        auto const release = reinterpret_cast<ContextReleaseFn>(contextVtable[3]);
        release(context);
    }

    // Release the globally cached controller/focus registrations.
    FUN_004086d0(&DAT_012069d4);
    FUN_004086d0(&DAT_012069ec);
    FUN_00408310(&DAT_01206a08);
    FUN_00408310(&DAT_01206a18);
    FUN_004086d0(&DAT_012069fc);
    FUN_00408310(&DAT_012069fc);
    FUN_004086d0(&DAT_01206a10);
    FUN_00408310(&DAT_01206a10);

    // Clear the active-manager singleton and notify the subsystem shutdown path.
    At<void**>(self, 0x0C) = &PTR_LAB_00e2f494;
    DAT_012233b4 = 0;
    FUN_004083d0();
}

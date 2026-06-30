// FUNC_NAME: InputDevice::applyFlags

#include <cstdint>

// Forward declarations of global functions found in the binary
extern bool IsInputEnabled();          // FUN_00481660
extern void SetInputFlags(uint32_t flags); // FUN_004816c0

void __thiscall InputDevice::applyFlags(uint32_t flags) {
    // Check if input system is globally enabled
    if (!IsInputEnabled()) {
        return;
    }

    // Check conditions to clear bit 1 (0x02) from flags
    // +0x10: pointer to associated device object; 0x48 is a specific device type (maybe vibration device?)
    // +0x109: byte flag indicating "force feedback disabled" or similar
    if ((*(int32_t*)(this + 0x10) != 0 && *(int32_t*)(this + 0x10) != 0x48) ||
        *(int8_t*)(this + 0x109) != 0) {
        flags &= ~0x02; // Clear bit 1
    }

    // Further check: if bit 1 is set but bit 0 is not, and a virtual function returns false,
    // then clear bit 1.
    if ((flags & 0x02) && !(flags & 0x01)) {
        // The vtable is located at offset -0x58 from this pointer
        // (likely due to multiple inheritance or a base class at that offset)
        // Vtable entry at offset 0x14c is the virtual function canApplyFlags()
        uintptr_t** vtablePtr = reinterpret_cast<uintptr_t**>(
            reinterpret_cast<char*>(this) - 0x58
        );
        // Function pointer type: bool (__thiscall)(void*)
        using CanApplyFunc = bool (__thiscall*)(void*);
        CanApplyFunc canApply = reinterpret_cast<CanApplyFunc>(
            reinterpret_cast<uintptr_t*>(*vtablePtr)[0x14c / sizeof(uintptr_t)]
        );
        // this pointer for the virtual call is the object at (this - 0x58)
        void* baseObj = reinterpret_cast<char*>(this) - 0x58;
        if (!canApply(baseObj)) {
            flags &= ~0x02;
        }
    }

    // If flags remain non‑zero, apply them via the global function
    if (flags != 0) {
        SetInputFlags(flags);
    }
}
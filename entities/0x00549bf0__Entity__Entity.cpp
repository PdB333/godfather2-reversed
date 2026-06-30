// FUNC_NAME: Entity::Entity
// Constructor for base Entity class. Initializes vtable, sub-object, and default fields.
// Address: 0x00549bf0

#include <cstdint>

// Forward declarations
extern void* PTR_FUN_00e39bc8; // vtable pointer for Entity
extern uint32_t DAT_00e2b1a4;  // global handle/ID constant (e.g., invalid handle)

// Sub-object initialization function (likely base class or member init)
void __fastcall sub_549b60(int param_1, void* param_2, int param_3);

// Static initialization function (e.g., random seed or global state)
void __cdecl sub_45cbe0();

class Entity {
public:
    // Vtable pointer at offset 0x00
    void* vtable;

    // Fields at various offsets (relative to this)
    // +0x04: unknown (maybe flags)
    // +0x08: unknown
    // +0x0C: unknown
    // +0x10: field4 (set to DAT_00e2b1a4)
    // +0x14: unknown
    // +0x18: unknown
    // +0x1C: unknown
    // +0x20: unknown
    // +0x24: field9 (set to DAT_00e2b1a4)
    // +0x28: unknown
    // +0x2C: unknown
    // +0x30: unknown
    // +0x34: unknown
    // +0x38: fieldE (set to DAT_00e2b1a4)
    // +0x3C: unknown
    // +0x40: field10 (zeroed)
    // +0x44: field11 (zeroed)
    // +0x48: field12 (zeroed)
    // +0x4C: field13 (zeroed)
    // ...
    // +0x10C: field43 (zeroed)
    // +0x110: field44 (zeroed)

    // Constructor
    __thiscall Entity() {
        // Set vtable
        this->vtable = &PTR_FUN_00e39bc8;

        // Initialize sub-object at offset 0x10 (param_1+4)
        sub_549b60(0, reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + 0x10), 0);

        // Zero out fields at offsets 0x10C and 0x110
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x10C) = 0;
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x110) = 0;

        // Call static initialization
        sub_45cbe0();

        // Load global handle and assign to three fields
        uint32_t handle = DAT_00e2b1a4;
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x10) = handle;  // field4
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x24) = handle;  // field9
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x38) = handle;  // fieldE

        // Zero out four consecutive fields at offsets 0x40-0x4C
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x40) = 0; // field10
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x44) = 0; // field11
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x48) = 0; // field12
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x4C) = 0; // field13
    }
};
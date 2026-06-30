// FUNC_NAME: Player::Player

#include <cstdint>

// External vtable symbols
extern void *PTR_FUN_00d58928;
extern void *PTR_LAB_00d58918;
extern void *PTR_LAB_00d58914;
extern void *PTR_FUN_00d5888c;
extern void *PTR_LAB_00d5887c;
extern void *PTR_LAB_00d58878;

// Forward declarations for sub‑constructors (called via thiscall)
void __thiscall FUN_006b8060(Player *this);
void __thiscall FUN_0046c640(Player *this);

class Player {
public:
    void *vfptr;                      // +0x00 primary vtable
    // ... other members ...
    void *vtable_interface1;          // +0x3C (index 0xF)
    void *vtable_interface2;          // +0x48 (index 0x12)
    // ... rest ...
};

// Constructor at 0x006853E0
void __thiscall Player::Player(Player *thisPtr)
{
    // — Stage 1: set initial vtable and interface pointers —
    // Set primary vtable to initial base class vtable
    thisPtr->vfptr = &PTR_FUN_00d58928;
    // Set interface vtable at offset +0x3C
    reinterpret_cast<void**>(thisPtr)[0xF] = &PTR_LAB_00d58918;
    // Set interface vtable at offset +0x48
    reinterpret_cast<void**>(thisPtr)[0x12] = &PTR_LAB_00d58914;

    // Call first base class constructor
    FUN_006b8060(thisPtr);

    // — Stage 2: switch vtable to derived class and set new interfaces —
    // Overwrite primary vtable with derived class vtable
    thisPtr->vfptr = &PTR_FUN_00d5888c;
    // Update interface vtable at +0x3C to derived version
    reinterpret_cast<void**>(thisPtr)[0xF] = &PTR_LAB_00d5887c;
    // Update interface vtable at +0x48 to derived version
    reinterpret_cast<void**>(thisPtr)[0x12] = &PTR_LAB_00d58878;

    // Call second base class constructor (or final initializer)
    FUN_0046c640(thisPtr);
}
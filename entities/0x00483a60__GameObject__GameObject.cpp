// FUNC_NAME: GameObject::GameObject
// Function address: 0x00483a60
// Description: Constructor for a GameObject (EARS engine). Sets up vtable, initializes fields, calls external initialization, then sets final vtable.

#include <cstdint>

// Forward declaration of external initialization function
extern void FUN_0043eeb0(int param, int zero, int negOne);

class GameObject {
public:
    // Constructor: takes an integer parameter (likely an ID or handle)
    __thiscall GameObject(int someParam) {
        // Set base vtable temporarily (likely for base class construction)
        this->vtable = reinterpret_cast<void**>(&PTR_FUN_00da9810);

        // Set name field to "unknown" (offset +0x04)
        this->name = "unknown";

        // Initialize fields
        this->field_0x1C = 0;      // offset +0x1C
        this->field_0x20 = 0xF;    // offset +0x20

        // Clear byte at offset +0x0C
        *(reinterpret_cast<uint8_t*>(this) + 0x0C) = 0;

        // Call external initialization function (likely base class constructor or resource init)
        // Passes: someParam, 0, 0xFFFFFFFF (probably handle, type, flags)
        FUN_0043eeb0(someParam, 0, 0xFFFFFFFF);

        // Set final vtable for this class (after base init)
        this->vtable = reinterpret_cast<void**>(&PTR_FUN_00da9834);
    }

private:
    // Note: Offsets are based on Ghidra analysis of array indices (param_1[0], param_1[1], etc.)
    // Assuming standard 4-byte alignment on x86.

    void* vtable;                 // offset +0x00
    const char* name;             // offset +0x04
    // Padding: offsets +0x08 to +0x0B (possibly)
    uint8_t unknownByte;          // offset +0x0C (byte)
    // More padding to align to 4-byte boundaries
    int field_0x1C;               // offset +0x1C
    int field_0x20;               // offset +0x20
};

// Vtable symbols (actual addresses defined elsewhere)
extern void* PTR_FUN_00da9810;   // Base class vtable pointer
extern void* PTR_FUN_00da9834;   // Derived class vtable pointer
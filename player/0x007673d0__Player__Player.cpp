// FUNC_NAME: Player::Player
// Address: 0x007673d0
// Player constructor initializes the object from two parameters, sets up vtables and various state fields.

#include <cstdint>

class Player {
public:
    // Vtable pointer stored at offset 0x00
    void* vtable; // +0x00
    // ... other base class members ...
    // Offset 0x5C (0x17*4) is a pointer to some component
    void* componentPtr; // +0x5C
    // Offset 0x70 (0x1C*4) is secondary vtable
    void* secondaryVtable; // +0x70
    // Offset 0x74 (0x1D*4) is a 16-bit field (flags)
    uint16_t flags; // +0x74
    // Offset 0x78 (0x1E*4) is a 32-bit value from component+0x5C4
    uint32_t componentValue; // +0x78
    // Offset 0x7C (0x1F*4) is a counter or type
    uint32_t typeField; // +0x7C
    // Offset 0x80 (0x20*4) is a pointer from global
    void* globalPointer; // +0x80
    // Offset 0x84 (0x21*4) is reset to zero
    uint32_t zeroField; // +0x84

    // Constructor
    __thiscall Player(Player* this, void* param2, void* param3) {
        // Call base initialization (not a constructor with this; static-like call)
        InitializeBase(param2, param3); // FUN_0073e160

        // Load global pointer DAT_00d5d7b8
        void* global = *(void**)0x00d5d7b8;

        // Set main vtable
        this->vtable = (void*)0x00d65958;

        // Get component pointer from this+0x5C and read value at component+0x5C4
        void* comp = *(void**)((uint8_t*)this + 0x5C);
        this->componentValue = *(uint32_t*)((uint8_t*)comp + 0x5C4);

        // Set secondary vtable
        this->secondaryVtable = (void*)0x00d65948;

        // Set flags to 0xC000
        this->flags = 0xC000;

        // Set type to 4
        this->typeField = 4;

        // Set global pointer
        this->globalPointer = global;

        // Set zero field
        this->zeroField = 0;

        return this;
    }

private:
    // Static helper function (corresponds to FUN_0073e160)
    static void InitializeBase(void* param2, void* param3);
};
// FUNC_NAME: Player::Player
#include <cstddef>

// Virtual table pointers defined elsewhere in the binary
extern void* PTR_FUN_00d621d8;  // Main vtable for Player
extern void* PTR_LAB_00d621c8;  // Vtable at offset +0x3C (base interface)
extern void* PTR_LAB_00d621c4;  // Vtable at offset +0x48
extern void* PTR_LAB_00d621c0;  // Vtable at offset +0x50
extern void* PTR_LAB_00d62160;  // Vtable at offset +0x54
extern void* PTR_LAB_00d620f8;  // Vtable at offset +0x58

// Helper functions (from other parts of the binary)
void initializeBase();                    // FUN_0046ea20 - base class constructor
void* allocateObject(void* obj, size_t); // FUN_0043b960 - memory allocation/placement

// Reconstructed Player constructor (__thiscall)
void* __thiscall Player::Player(Player* this, byte param2)
{
    // Set vtable for the Player class itself
    this->vtable = &PTR_FUN_00d621d8;

    // Set up multiple inheritance interface pointers
    // +0x3C: first base class vtable (e.g., Sentient)
    *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(this) + 0x3C) = &PTR_LAB_00d621c8;
    // +0x48: second base class vtable (e.g., Entity)
    *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(this) + 0x48) = &PTR_LAB_00d621c4;
    // +0x50: third base class vtable
    *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(this) + 0x50) = &PTR_LAB_00d621c0;
    // +0x54: fourth base class vtable
    *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(this) + 0x54) = &PTR_LAB_00d62160;
    // +0x58: fifth base class vtable
    *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(this) + 0x58) = &PTR_LAB_00d620f8;

    // Call base constructor (initializes base subobjects)
    initializeBase();

    // If param2 bit 0 is set, allocate memory for the object (operator new)
    if ((param2 & 1) != 0)
    {
        allocateObject(this, 0x180); // Total object size = 384 bytes
    }

    // Return the constructed object pointer
    return this;
}
// FUNC_NAME: Player::Player
// Address: 0x00903440
// Role: Player object constructor with magic number initialization

#include <cstdint>

class Player {
public:
    void** vtable;                // +0x00 main vtable (PTR_FUN_00d81f50)
    // Unknown base class vtable at +0x3C
    // Another vtable at +0x48
    // Many fields follow, some with debug sentinel values

    Player(void* allocatorOrOwner /* param_2 */);

private:
    void initializeBase(void* allocatorOrOwner); // calls FUN_0046c590
};

// Constructor implementation
Player::Player(void* allocatorOrOwner) {
    // Call base class constructor (likely Sentient or similar)
    initializeBase(allocatorOrOwner);

    // Set vtable pointers (multiple inheritance or embedded subobjects)
    this->vtable = reinterpret_cast<void**>(&PTR_FUN_00d81f50); // main vtable
    this->atOffset0x3C = reinterpret_cast<void**>(&PTR_LAB_00d81f40); // +0x3C
    this->atOffset0x48 = reinterpret_cast<void**>(&PTR_LAB_00d81f3c); // +0x48

    // Initialize debug sentinel values for uninitialized memory detection
    this->debugField1 = 0xbadbadba;   // +0x14
    this->debugField2 = 0xbeefbeef;   // +0x15
    this->debugField3 = 0xeac15a55;   // +0x16
    this->debugField4 = 0x91100911;   // +0x17

    // Clear blocks of fields (likely arrays or structures)
    // Block 1: offsets 0x18-0x1A (3 ints) and half-words at 0x6C-0x6E
    this->field_0x18 = 0;
    this->field_0x19 = 0;
    this->field_0x1A = 0;
    *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(this) + 0x6C) = 0;
    *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(this) + 0x6E) = 0;

    // Block 2: offsets 0x1C and half-words at 0x74-0x76
    this->field_0x1C = 0;
    *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(this) + 0x74) = 0;
    *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(this) + 0x76) = 0;

    // Block 3: offsets 0x1E and half-words at 0x7C-0x7E
    this->field_0x1E = 0;
    *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(this) + 0x7C) = 0;
    *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(this) + 0x7E) = 0;

    // Block 4: offsets 0x20 and half-words at 0x84-0x86
    this->field_0x20 = 0;
    *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(this) + 0x84) = 0;
    *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(this) + 0x86) = 0;

    // Block 5: offsets 0x22 and half-words at 0x8C-0x8E
    this->field_0x22 = 0;
    *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(this) + 0x8C) = 0;
    *reinterpret_cast<uint16_t*>(reinterpret_cast<uint8_t*>(this) + 0x8E) = 0;

    // Additional fields
    this->field_0x24 = 0;
    this->field_0x25 = 0xFFFFFFFF;   // -1 sentinel at +0x94
    this->field_0x26 = DAT_00d5eee4;  // Global singleton pointer at +0x98
    this->field_0x27 = 0;             // +0x9C
    this->field_0x28 = 0;             // +0xA0
}
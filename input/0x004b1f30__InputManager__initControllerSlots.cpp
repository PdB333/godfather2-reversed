// FUNC_NAME: InputManager::initControllerSlots
// At address 0x004b1f30, this function initializes the InputManager's controller slot table to default values.
// The structure contains a header (0x00..0x84) and 16 ControllerSlot structures (each 0x5C bytes).
// Global default value DAT_00e2b1a4 is used as a sentinel (likely -1 or 0xFFFFFFFF).

#include <cstdint>

// Global constant used as default/invalid value
static const uint32_t kDefaultSlotValue = 0xFFFFFFFF; // placeholder; actual value from DAT_00e2b1a4

// External post-initialization function
extern void postInitFunction(); // corresponds to FUN_004b2060

class InputManager {
public:
    // Controller slot structure (0x5C bytes)
    struct ControllerSlot {
        uint32_t field_00; // +0x00
        uint32_t field_04; // +0x04
        uint32_t field_08; // +0x08
        uint32_t field_0c; // +0x0C
        uint32_t field_10; // +0x10
        uint32_t field_14; // +0x14
        uint8_t  field_18; // +0x18 (byte)
        uint32_t field_1c; // +0x1C
        uint32_t field_20; // +0x20
        uint32_t field_24; // +0x24
        uint32_t field_28; // +0x28
        uint32_t field_2c; // +0x2C
        uint32_t field_30; // +0x30
        uint32_t field_34; // +0x34
        uint32_t field_38; // +0x38
        uint32_t field_3c; // +0x3C
        uint32_t field_40; // +0x40
        uint32_t field_44; // +0x44
        uint32_t field_48; // +0x48
        uint32_t field_4c; // +0x4C
        uint32_t field_50; // +0x50
        uint32_t field_54; // +0x54
        uint32_t field_58; // +0x58
    };

    void __thiscall initControllerSlots();
};

void InputManager::initControllerSlots()
{
    // Pointer to the beginning of the object
    uint32_t* base = reinterpret_cast<uint32_t*>(this);

    // --- Initialize header fields (offsets 0x00 to 0x84) ---
    base[0] = 0;              // +0x00
    base[7] = 0;              // +0x1C
    base[8] = 0;              // +0x20
    base[9] = 0;              // +0x24
    base[10] = 0;             // +0x28
    base[0xd] = 0;            // +0x34
    base[0xc] = 0;            // +0x30
    base[0xb] = 0;            // +0x2C
    base[0x10] = 0;           // +0x40
    base[0xf] = 0;            // +0x3C
    base[0xe] = 0;            // +0x38
    *(uint8_t*)(base + 0x11) = 0; // +0x44 (byte)
    base[0x12] = kDefaultSlotValue; // +0x48
    base[0x13] = 0;           // +0x4C
    base[0x14] = 0;           // +0x50
    base[0x15] = 0;           // +0x54
    base[0x16] = 0;           // +0x58
    base[0x17] = kDefaultSlotValue; // +0x5C
    base[0x18] = 0;           // +0x60
    base[0x19] = 0;           // +0x64
    base[0x1a] = 0;           // +0x68
    base[0x1b] = 0;           // +0x6C
    base[0x1c] = kDefaultSlotValue; // +0x70
    base[0x1d] = 0;           // +0x74
    base[0x1e] = 0;           // +0x78
    base[0x1f] = 0;           // +0x7C
    base[0x20] = 0;           // +0x80
    base[0x21] = kDefaultSlotValue; // +0x84

    // --- Initialize 16 controller slots starting at offset 0x88 (base + 0x22) ---
    // Each slot is 0x17 dwords = 0x5C bytes
    for (int i = 0; i < 16; i++)
    {
        uint32_t* slotBase = base + 0x22 + i * 0x17;

        slotBase[2] = 0;                  // +0x08
        slotBase[1] = 0;                  // +0x04
        slotBase[0] = 0;                  // +0x00
        slotBase[5] = 0;                  // +0x14
        slotBase[4] = 0;                  // +0x10
        slotBase[3] = 0;                  // +0x0C
        *(uint8_t*)(slotBase + 6) = 0;    // +0x18 (byte)
        slotBase[7] = kDefaultSlotValue;  // +0x1C
        slotBase[8] = 0;                  // +0x20
        slotBase[9] = 0;                  // +0x24
        slotBase[10] = 0;                 // +0x28
        slotBase[0xb] = 0;                // +0x2C
        slotBase[0xc] = kDefaultSlotValue;// +0x30
        slotBase[0xd] = 0;                // +0x34
        slotBase[0xe] = 0;                // +0x38
        slotBase[0xf] = 0;                // +0x3C
        slotBase[0x10] = 0;               // +0x40
        slotBase[0x11] = kDefaultSlotValue;// +0x44
        slotBase[0x12] = 0;               // +0x48
        slotBase[0x13] = 0;               // +0x4C
        slotBase[0x14] = 0;               // +0x50
        slotBase[0x15] = 0;               // +0x54
        slotBase[0x16] = kDefaultSlotValue;// +0x58
    }

    // Call post‑initialization routine
    postInitFunction();
}
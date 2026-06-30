// FUNC_NAME: InputActionSet::InputActionSet
// Function at 0x00475b90: Constructor for InputActionSet, initializes 8 action slots with sentinel values.
// Calls base class constructor at 0x0046c590 (likely InputActionSet::baseCtor or similar).
// Structure: this +0x00 vtable, +0x3C pointer, +0x48 pointer, +0x50 DWORD, +0x54 WORD, +0x56 WORD,
// then 8 InputSlot (each 16 bytes) at +0x58, then DWORD at +0xD8 (terminator).

#include <cstdint>

struct InputSlot {
    uint32_t type;   // +0x00  (0xbadbadba = invalid)
    uint32_t param1; // +0x04  (0xbeefbeef)
    uint32_t param2; // +0x08  (0xeac15a55)
    uint32_t flags;  // +0x0C  (0x91100911 = valid/ready)
};

// Forward declaration of base class constructor
void __thiscall InputActionSet_baseCtor(uint32_t param_2); // FUN_0046c590

class InputActionSet {
public:
    inline static constexpr uint32_t kSlotCount = 8; // 8 slots
    inline static constexpr uint32_t kInvalidType = 0xbadbadba;
    inline static constexpr uint32_t kInitialFlags = 0x91100911;
    inline static constexpr uint32_t kInitParam1 = 0xbeefbeef;
    inline static constexpr uint32_t kInitParam2 = 0xeac15a55;

    // Constructor
    void* __thiscall InputActionSet(uint32_t param_2)
    {
        // Call base class initializer
        InputActionSet_baseCtor(param_2);

        // Set vtable and sub-function tables
        this->vtable = &PTR_FUN_00e32e48;          // +0x00
        this->subTable1 = &PTR_LAB_00e32e64;       // +0x3C (0xF*4)
        this->subTable2 = &PTR_LAB_00e32e74;       // +0x48 (0x12*4)

        // Basic fields
        this->field_0x14_50 = 0;                    // +0x50 DWORD
        this->field_0x15_54 = 0;                    // +0x54 WORD
        this->field_0x56 = 0;                       // +0x56 WORD

        // Initialize each slot with sentinel values
        for (int i = 0; i < kSlotCount; ++i) {
            InputSlot& slot = this->slots[i];       // +0x58 + i*16
            slot.type   = kInvalidType;              // +0x00
            slot.param1 = kInitParam1;               // +0x04
            slot.param2 = kInitParam2;               // +0x08
            slot.flags  = kInitialFlags;              // +0x0C
        }

        // Terminator after last slot
        this->terminator = 0;                       // +0xD8 (0x36*4)

        return this;
    }

private:
    // Layout (all offsets relative to this):
    void* vtable;                           // +0x00
    /* ... other base members ... */
    void* subTable1;                        // +0x3C (offset 0xF*4)
    void* subTable2;                        // +0x48 (offset 0x12*4)

    uint32_t field_0x14_50;                 // +0x50
    uint16_t field_0x15_54;                 // +0x54 (WORD)
    uint16_t field_0x56;                    // +0x56 (WORD)

    InputSlot slots[kSlotCount];            // +0x58, each slot 16 bytes

    uint32_t terminator;                    // +0xD8
};
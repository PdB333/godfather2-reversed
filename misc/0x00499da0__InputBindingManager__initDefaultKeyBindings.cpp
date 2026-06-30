// FUNC_NAME: InputBindingManager::initDefaultKeyBindings

#include <cstdint>

// Structure for a key binding pair: action code + modifier flags
struct KeyBinding {
    int32_t actionCode;   // e.g., 0x3c8 (968), 0x2cb (715), 0x1e (30)
    int32_t modifierFlags; // typically 0x300ff (keyboard flag?)
};

// Maximum number of default bindings (42 pairs = 84 dwords, see loop count 0x54=84)
#define MAX_DEFAULT_BINDINGS 42

class InputBindingManager {
public:
    void initDefaultKeyBindings() {
        // Vtable pointer (set by caller in the constructor)
        this->vtable = &s_vtable;

        // Zero out the header fields and the entire binding array
        this->field_1 = 0;  // +0x04
        this->field_2 = 0;  // +0x08
        this->field_3 = 0;  // +0x0C
        this->field_4 = 0;  // +0x10
        this->bindings[0].actionCode = 0;      // +0x18 (index 6)
        this->bindings[0].modifierFlags = 0;   // +0x1C (index 7)

        // Copy the zeroed first pair to the rest of the array (0x54 dwords = 84 dwords = 42 pairs)
        for (int i = 0; i < MAX_DEFAULT_BINDINGS - 1; i++) {
            this->bindings[i + 1] = this->bindings[0];
        }

        // Now set the header fields again (they were zeroed by the copy? Actually the copy only affects the array starting at index 8.)
        this->field_1 = 0;
        this->field_2 = 0;
        this->field_3 = 0;
        this->field_4 = 0;
        this->bindings[0] = { 0, 0 }; // redundant, but follows original code

        // Initialize default key bindings
        // Each pair: action code and modifier flags (0x300FF suggests keyboard press)
        this->bindings[0] = { 0x3c8, 0x300ff }; // Action 968 (e.g., vehicle? )
        this->bindings[1] = { 0x2cb, 0x300ff }; // Action 715
        this->bindings[2] = { 0x5d0, 0x300ff }; // Action 1488
        this->bindings[3] = { 0x4cd, 0x300ff }; // Action 1229

        // Common movement keys (DIK codes)
        this->bindings[10] = { 0x1c12, 0x300ff }; // Action 7186? 
        this->bindings[11] = { 0x13,  0x300ff }; // DIK_R (19)
        this->bindings[13] = { 0x39,  0x300ff }; // DIK_SPACE (57)
        this->bindings[12] = { 0x2a,  0x300ff }; // DIK_LSHIFT (42)
        this->bindings[15] = { 0xf,   0x300ff }; // DIK_TAB? (15)
        this->bindings[14] = { 1,     0x300ff }; // Escape? (1)
        this->bindings[11] = { 0x1d,  0x300ff }; // DIK_LCTRL (29) - note: overwriting previous entry at index 11

        // WASD keys
        this->bindings[9]  = { 0x11,  0x300ff }; // DIK_W (17)
        this->bindings[8]  = { 0x1e,  0x300ff }; // DIK_A (30)
        this->bindings[7]  = { 0x1f,  0x300ff }; // DIK_S (31)
        this->bindings[6]  = { 0x20,  0x300ff }; // DIK_D (32)

        // Additional actions
        this->bindings[5]  = { 0x2a,  0x300ff }; // DIK_LSHIFT again (42) - different index
        this->bindings[4]  = { 0x1d,  0x300ff }; // DIK_LCTRL? (29) - overwritten below

        // Set header fields again (final values)
        this->field_1 = 1; // +0x04
        this->field_2 = 2; // +0x08
    }

private:
    // vtable pointer
    void* vtable; // +0x00

    // Unknown fields, likely counts or modes
    int32_t field_1; // +0x04
    int32_t field_2; // +0x08
    int32_t field_3; // +0x0C
    int32_t field_4; // +0x10

    // Binding array (42 pairs, from +0x18 to +0x168)
    KeyBinding bindings[MAX_DEFAULT_BINDINGS]; // +0x18

    // External vtable reference
    static void* s_vtable;
};

// The vtable pointer is defined elsewhere (PTR_LAB_00e35048)
void* InputBindingManager::s_vtable = (void*)0x00e35048; // placeholder address
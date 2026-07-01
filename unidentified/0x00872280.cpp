// FUN_NAME: PlayerSM::PlayerSM
// Address: 0x00872280 - Constructor for PlayerSM (Player State Machine)
// Initializes vtable pointers, zeroes state fields, and sets default values.

#include <cstdint>

// Forward declaration of base class constructor (FUN_00724ea0)
void __thiscall BasePlayerStateMachineConstructor(uint32_t* param_2); // assuming param_2 is a this pointer

// Extern globals for default values
extern uint32_t DAT_00d761cc; // Default value for field +0x160
extern uint32_t DAT_00d76184; // Default value for field +0x164

// Vtable/function pointer tables (referenced as PTR_LAB_* and PTR_FUN_*)
extern void* PTR_FUN_00d761a0;  // Primary vtable at +0x00
extern void* PTR_LAB_00d76190;  // Secondary vtable at +0x3C (offset 0xF * 4)
extern void* PTR_LAB_00d7618c;  // Tertiary vtable at +0x48 (offset 0x12 * 4)
extern void* PTR_LAB_00d76188;  // Quaternary vtable at +0x50 (offset 0x14 * 4)

class PlayerSM {
public:
    // Constructor
    PlayerSM(uint32_t param_2) {
        // Call base class constructor (likely initializes parent)
        BasePlayerStateMachineConstructor(&param_2);

        // Set up virtual function tables (multiple inheritance)
        this->vtable = &PTR_FUN_00d761a0;          // +0x00
        this->vtable2 = &PTR_LAB_00d76190;         // +0x3C (offset 0xF)
        this->vtable3 = &PTR_LAB_00d7618c;         // +0x48 (offset 0x12)
        this->vtable4 = &PTR_LAB_00d76188;         // +0x50 (offset 0x14)

        // Zero out state fields at high offsets
        this->field_0x14C = 0;   // +0x53
        this->field_0x148 = 0;   // +0x52
        this->field_0x144 = 0;   // +0x51
        this->field_0x140 = 0;   // +0x50

        // Set default states
        this->field_0x150 = 1;   // +0x54 (e.g., default active state)
        this->field_0x154 = 0;   // +0x55
        this->field_0x158 = 0;   // +0x56

        // Load global defaults for timing/scale
        this->field_0x160 = DAT_00d761cc; // +0x58
        this->field_0x15C = 0;           // +0x57
        this->field_0x164 = DAT_00d76184; // +0x59

        // Return this (implied by __thiscall)
    }

private:
    // Vtable pointers (multiple inheritance)
    void* vtable;        // +0x00
    // ... other base class members ...
    void* vtable2;       // +0x3C (0xF words)
    void* vtable3;       // +0x48 (0x12 words)
    void* vtable4;       // +0x50 (0x14 words)

    // State fields
    uint32_t field_0x140; // +0x50
    uint32_t field_0x144; // +0x51
    uint32_t field_0x148; // +0x52
    uint32_t field_0x14C; // +0x53
    uint32_t field_0x150; // +0x54
    uint32_t field_0x154; // +0x55
    uint32_t field_0x158; // +0x56
    uint32_t field_0x15C; // +0x57
    uint32_t field_0x160; // +0x58
    uint32_t field_0x164; // +0x59
};
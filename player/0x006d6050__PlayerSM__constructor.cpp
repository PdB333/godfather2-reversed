// FUNC_NAME: PlayerSM::constructor
// Function address: 0x006d6050
// Role: Constructor for PlayerSM class (state machine base)
// Initializes vtable, function pointers, and zeroes out state variables

#include <cstdint>

class PlayerSM {
public:
    // Vtable pointer at +0x00
    void** vtable;

    // Unknown function pointers at offsets +0x3C (0xF) and +0x48 (0x12)
    void* m_stateFunc1;   // +0x3C
    void* m_stateFunc2;   // +0x48

    // State timer or counter at +0x50 (0x14)
    int32_t m_stateTimer; // +0x50

    // Two 2-byte flags at +0x54 and +0x56
    uint16_t m_flagsLow;  // +0x54
    uint16_t m_flagsHigh; // +0x56

    // Additional state variables at +0x58, +0x5C, +0x60, +0x64, +0x68
    int32_t m_stateVar1;  // +0x58
    int32_t m_stateVar2;  // +0x5C
    int32_t m_stateVar3;  // +0x60
    int32_t m_stateVar4;  // +0x64
    int32_t m_stateVar5;  // +0x68

    // Constructor
    PlayerSM(void* param_2);
};

// External base class constructor (likely from a parent class)
extern void FUN_0046c590(void* param_2);

// External vtable and function pointers (defined elsewhere)
extern void* PTR_FUN_00d5f45c; // vtable
extern void* PTR_LAB_00d5f44c; // state function pointer 1
extern void* PTR_LAB_00d5f448; // state function pointer 2

PlayerSM::PlayerSM(void* param_2) {
    // Call base class constructor
    FUN_0046c590(param_2);

    // Set vtable pointer
    this->vtable = &PTR_FUN_00d5f45c;

    // Initialize state function pointers
    this->m_stateFunc1 = &PTR_LAB_00d5f44c; // +0x3C
    this->m_stateFunc2 = &PTR_LAB_00d5f448; // +0x48

    // Zero out state variables
    this->m_stateTimer = 0;   // +0x50
    this->m_flagsLow = 0;     // +0x54
    this->m_flagsHigh = 0;    // +0x56
    this->m_stateVar1 = 0;    // +0x58
    this->m_stateVar2 = 0;    // +0x5C
    this->m_stateVar3 = 0;    // +0x60
    this->m_stateVar4 = 0;    // +0x64
    this->m_stateVar5 = 0;    // +0x68
}
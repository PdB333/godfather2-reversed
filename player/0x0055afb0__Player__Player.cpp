// FUNC_NAME: Player::Player
// Address: 0x0055afb0
// Role: Constructor for Player class, initializes base class, vtable pointers, and member variables.

#include <cstdint>

// Forward declarations of called functions
void __fastcall SentientConstructor(void* thisPtr); // FUN_00544320
void __fastcall initSubObject1(); // FUN_0049ccc0
void __fastcall initSubObject2(); // FUN_004bfcf0

// Vtable pointers (from global data)
extern void* g_vtable_Player;          // PTR_FUN_00e3a080
extern void* g_vtable_Player_0x3C;     // PTR_LAB_00e3a2e0
extern void* g_vtable_Player_0x48;     // PTR_LAB_00e3a2f0
extern void* g_vtable_Player_0x50;     // PTR_LAB_00e3a2f4
extern void* g_vtable_Player_0x54;     // PTR_LAB_00e3a2f8
extern void* g_vtable_Player_0x58;     // PTR_LAB_00e3a358
extern void* g_vtable_Player_0x2E0;    // PTR_LAB_00e3a3bc
extern void* g_vtable_Player_0x2E4;    // PTR_LAB_00e3a3d0

// Global initial values
extern uint32_t g_initialValue1; // DAT_00e2b1a4
extern uint32_t g_initialValue2; // DAT_00e2cd14
extern uint32_t g_initialValue3; // DAT_00e2b050
extern uint32_t g_initialValue4; // DAT_00e2e230

class Player {
public:
    // Constructor
    Player() __thiscall {
        // Call base class constructor (Sentient)
        SentientConstructor(this);

        // Set primary vtable
        *(void**)this = g_vtable_Player;

        // Set additional vtable pointers for interfaces
        *(void**)((uint8_t*)this + 0x3C) = g_vtable_Player_0x3C;  // +0x3C
        *(void**)((uint8_t*)this + 0x48) = g_vtable_Player_0x48;  // +0x48
        *(void**)((uint8_t*)this + 0x50) = g_vtable_Player_0x50;  // +0x50
        *(void**)((uint8_t*)this + 0x54) = g_vtable_Player_0x54;  // +0x54
        *(void**)((uint8_t*)this + 0x58) = g_vtable_Player_0x58;  // +0x58
        *(void**)((uint8_t*)this + 0x2E0) = g_vtable_Player_0x2E0; // +0x2E0
        *(void**)((uint8_t*)this + 0x2E4) = g_vtable_Player_0x2E4; // +0x2E4

        // Zero-initialize a block of fields (offsets 0x3A4 to 0x3B0)
        *(uint32_t*)((uint8_t*)this + 0x3A4) = 0; // +0x3A4
        *(uint32_t*)((uint8_t*)this + 0x3A8) = 0; // +0x3A8
        *(uint32_t*)((uint8_t*)this + 0x3AC) = 0; // +0x3AC
        *(uint32_t*)((uint8_t*)this + 0x3B0) = 0; // +0x3B0

        // Zero-initialize more fields (offsets 0x480, 0x484)
        *(uint32_t*)((uint8_t*)this + 0x480) = 0; // +0x480
        *(uint32_t*)((uint8_t*)this + 0x484) = 0; // +0x484

        // Initialize three sub-objects (e.g., arrays or components)
        for (int i = 0; i < 3; ++i) {
            initSubObject1(); // FUN_0049ccc0
        }

        // Zero-initialize a large block (offsets 0x710 to 0x73C)
        for (int offset = 0x710; offset <= 0x73C; offset += 4) {
            *(uint32_t*)((uint8_t*)this + offset) = 0;
        }

        // Set initial values from global data (offsets 0x790 to 0x7A0)
        *(uint32_t*)((uint8_t*)this + 0x790) = g_initialValue1; // +0x790
        *(uint32_t*)((uint8_t*)this + 0x794) = g_initialValue2; // +0x794
        *(uint32_t*)((uint8_t*)this + 0x798) = g_initialValue3; // +0x798
        *(uint32_t*)((uint8_t*)this + 0x79C) = g_initialValue4; // +0x79C
        *(uint32_t*)((uint8_t*)this + 0x7A0) = 0;               // +0x7A0

        // Initialize four more sub-objects
        for (int i = 0; i < 4; ++i) {
            initSubObject2(); // FUN_004bfcf0
        }
    }
};
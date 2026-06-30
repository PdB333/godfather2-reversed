// FUNC_NAME: PlayerGroundSM::PlayerGroundSM
// Address: 0x006dd1b0
// Role: Constructor for PlayerGroundSM (player ground state machine). Initializes vtable, copies some state from parent (offsets 0x38/0x39), zeros many member variables (position, velocity, orientation, flags, etc.).

#include <cstdint>

// Forward declarations for called functions
void BaseClassInit(uint32_t param2, uint32_t globalData);  // FUN_006c9760
void SomeInitFunction();                                    // FUN_006dc940

// Global vtable symbol (assumed from game's vtable table)
extern void* g_vtable_PlayerGroundSM;   // PTR_FUN_00d5f6a4
extern void* g_someOtherPtr;            // PTR_LAB_00d5f69c

// This constructor is called with an initializer parameter
void* __thiscall PlayerGroundSM::PlayerGroundSM(void* this, void* initializer)
{
    // Call base class initialization with initializer and a global data pointer
    BaseClassInit((uint32_t)initializer, _DAT_00d5cf70);

    // Set vtable pointer
    *(uint32_t*)this = (uint32_t)&g_vtable_PlayerGroundSM;

    // Set another pointer at offset 0x08 (index 2)
    *(uint32_t*)((uint8_t*)this + 8) = (uint32_t)&g_someOtherPtr;

    // Call another initialization routine (likely derived class specific)
    SomeInitFunction();

    // Copy state from offsets 0xE0 and 0xE4 (0x38*4) to 0x2A4 and 0x2A8 (0xA9*4, 0xAA*4)
    *(uint32_t*)((uint8_t*)this + 0x2A4) = *(uint32_t*)((uint8_t*)this + 0xE0);
    *(uint32_t*)((uint8_t*)this + 0x2A8) = *(uint32_t*)((uint8_t*)this + 0xE4);

    // Zero out many fields (likely position, velocity, orientation, flags, etc.)
    // Offset 0x260: index 0x98 *4
    *(uint32_t*)((uint8_t*)this + 0x260) = 0;   // +0x260
    *(uint32_t*)((uint8_t*)this + 0x2A0) = 0;   // offset 0xA9? Wait, already set above. Actually offset 0x2A4 is set earlier, but 0x2A0 is index 0xA8? No, index 0x98 is 0x260, index 0xA9 is 0x2A4. Let's zero systematically.
    // We'll align with the indices as given in decompiled code.
    // Zero all indicated fields:
    uint32_t* base = (uint32_t*)this;
    base[0x98] = 0;   // +0x260
    base[0x99] = 0;   // +0x264
    base[0x9A] = 0;   // +0x268
    base[0xA1] = 0;   // +0x284
    base[0xA3] = 0;   // +0x28C
    base[0xA5] = 0;   // +0x294
    base[0xA6] = 0;   // +0x298
    base[0xA7] = 0;   // +0x29C
    base[0xA8] = 0;   // +0x2A0
    // Note: base[0xA9] and base[0xAA] are already set from copy above.
    base[0xAC] = 0;   // +0x2B0
    base[0xAD] = 0;   // +0x2B4
    base[0xAE] = 0;   // +0x2B8
    base[0xAF] = 0;   // +0x2BC
    base[0xB0] = 0;   // +0x2C0
    base[0xB1] = 0;   // +0x2C4
    base[0xB2] = 0;   // +0x2C8
    base[0xB3] = 0;   // +0x2CC
    base[0x88] = 0;   // +0x220

    // Byte fields at half-word offsets
    *(uint8_t*)((uint8_t*)this + 0x288) = 0;   // index 0xA2 *4 = 0x288, but as byte? Actually the decompiled says *(undefined1 *)(param_1 + 0xa2) -> that's byte at offset 0xA2*4? Wait param_1 is uint32*, so param_1+0xA2 adds 0xA2*4. But the cast to undefined1* means it's treating as byte offset. In Ghidra, param_1 is uint32*, so param_1 + 0xA2 increments by 4 bytes per index. But the cast to undefined1* suggests they are taking the byte address of that element. Actually the decompiled line: *(undefined1 *)(param_1 + 0xa2) means: take param_1 (which is a pointer to uint32), add 0xa2 (i.e., offset 0xA2*4 = 0x288), then cast that address to uint8*, and write 0. So it's a byte at offset 0x288. Similarly others.
    // To match: offset 0xA2*4 = 0x288
    *(uint8_t*)((uint8_t*)this + 0x288) = 0;
    *(uint8_t*)((uint8_t*)this + 0x290) = 0;   // index 0xA4*4 = 0x290
    *(uint8_t*)((uint8_t*)this + 0x2AC) = 0;   // index 0xAB*4 = 0x2AC

    base[0xB4] = 0;   // +0x2D0
    base[0x8B] = 0;   // +0x22C
    base[0x8A] = 0;   // +0x228
    base[0x89] = 0;   // +0x224
    base[0x8E] = 0;   // +0x238
    base[0x8D] = 0;   // +0x234
    base[0x8C] = 0;   // +0x230
    base[0x91] = 0;   // +0x244
    base[0x90] = 0;   // +0x240
    base[0x8F] = 0;   // +0x23C
    base[0x94] = 0;   // +0x250
    base[0x93] = 0;   // +0x24C
    base[0x92] = 0;   // +0x248
    base[0x97] = 0;   // +0x25C
    base[0x96] = 0;   // +0x258
    base[0x95] = 0;   // +0x254
    base[0x9D] = 0;   // +0x274
    base[0x9C] = 0;   // +0x270
    base[0x9B] = 0;   // +0x26C
    base[0xA0] = 0;   // +0x280
    base[0x9F] = 0;   // +0x27C
    base[0x9E] = 0;   // +0x278

    return this;
}
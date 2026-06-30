// FUNC_NAME: Player::Player (constructor at 0x00595dc0)
// Reconstructed from Ghidra decompilation – The Godfather 2 (2008, EA EARS engine)

#include <cstdint>

// Base class constructor (at 0x0059b5e0)
extern void __thiscall PlayerBaseConstructor(void* thisPtr);

// Global function pointer table (at 0x012055a8)
extern void* g_pInitTable; // *DAT_012055a8

// Class definition (partial – only fields initialized in this constructor)
class Player {
public:
    // Base class fields (not shown)

    // Player‑specific fields (offsets relative to `this`)
    // +0x70..0x78: three initial zeroes
    int32_t m_field70;
    int32_t m_field74;
    int32_t m_field78;

    // +0x7c (int)
    int32_t m_field7c;

    // +0x80, +0x82 (two shorts)
    int16_t m_field80;
    int16_t m_field82;

    // +0x84 (short, set to 4)
    int16_t m_maxSomething;   // e.g. max number of items/states

    // +0x86 (short)
    int16_t m_field86;

    // +0x88 (int)
    int32_t m_field88;

    // +0x8c: first sub‑object (12 bytes, e.g. a vector or state machine)
    uint8_t m_subObject1[12];

    // +0x98: second sub‑object (12 bytes)
    uint8_t m_subObject2[12];

    // +0xa4, +0xa8, +0xac (three ints)
    int32_t m_fieldA4;
    int32_t m_fieldA8;
    int32_t m_fieldAC;

    // Constructor
    Player() {
        // Call base class constructor (0x0059b5e0)
        PlayerBaseConstructor(this);

        // Initialize all explicit zero/constant fields
        m_field70 = 0;
        m_field74 = 0;
        m_field78 = 0;

        m_field80 = 0;
        m_field82 = 0;
        m_field88 = 0;
        m_field86 = 0;
        m_field7c = 0;

        m_maxSomething = 4;   // some constant, e.g. max targets or actions

        // Initialize two sub‑objects via a function from the global table
        // The function at offset 0x34 of *g_pInitTable is called with (0,0,0, address)
        typedef void (__cdecl *SubInitFunc)(int a1, int a2, int a3, void* mem);
        SubInitFunc initSubObj = (SubInitFunc)( ((uint32_t*)g_pInitTable)[0x34 / 4] );
        initSubObj(0, 0, 0, m_subObject1);
        initSubObj(0, 0, 0, m_subObject2);

        // Zero remaining fields
        m_fieldA4 = 0;
        m_fieldA8 = 0;
        m_fieldAC = 0;
    }
};
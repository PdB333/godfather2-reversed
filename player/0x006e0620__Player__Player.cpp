// FUNC_NAME: Player::Player
// Function address: 0x006e0620
// Role: Constructor for Player class – initializes vtable, zeros large number of fields (vectors, flags, etc.)

#include <cstdint>

// Forward declarations for base constructor and static initialization
extern void __thiscall Entity::Entity(void* thisPtr, void* param); // FUN_006c9760
extern void __cdecl initializePlayerStatics(); // FUN_006e01d0

// Global used by base constructor (likely a singleton or default allocator)
extern void* g_playerBaseGlobal; // _DAT_00d5cf70

// Vtable symbols (from Ghidra)
extern void* const VTABLE_Player;   // PTR_FUN_00d5f784
extern void* const VTABLE_Player_Base; // PTR_LAB_00d5f77c

class Player {
public:
    // Vtable pointer at +0x00
    void* m_vtable;
    // Secondary vtable (multiple inheritance base) at +0x08
    void* m_baseVtable;

    // Offsets based on decompiled param_1[...] indices:
    // +0x0C – +0x0E: (uninitialized in this constructor)
    // ...
    // Vector triples (likely position, velocity, acceleration, rotation, etc.)
    // +0xC0 (param_1[0x30]): m_vec0[0]
    // +0xC4 (param_1[0x31]): m_vec0[1]
    // +0xC8 (param_1[0x32]): m_vec0[2]
    // +0xCC (param_1[0x33]): m_vec1[0]
    // +0xD0 (param_1[0x34]): m_vec1[1]
    // +0xD4 (param_1[0x35]): m_vec1[2]
    // +0xD8 (param_1[0x36]): m_vec2[0]
    // +0xDC (param_1[0x37]): m_vec2[1]
    // +0xE0 (param_1[0x38]): m_vec2[2]
    // +0xE4 (param_1[0x39]): m_vec3[0]
    // +0xE8 (param_1[0x3A]): m_vec3[1]
    // +0xEC (param_1[0x3B]): m_vec3[2]
    // +0xF0 (param_1[0x3C]): m_uint0
    // +0xF4 (param_1[0x3D]): m_uint1
    // +0xF8 (param_1[0x3E]): m_uint2
    // +0xFC (param_1[0x3F]): m_uint3
    // +0x100 (param_1[0x40]): m_uint4
    // +0x104 (param_1[0x41]): m_uint5
    // +0x108 (byte) (param_1+0x42): m_byte0
    // +0x109 (byte): m_byte1
    // +0x10A (byte): m_byte2
    // +0x10C (param_1[0x43]): m_vec4[0]
    // +0x110 (param_1[0x44]): m_vec4[1]
    // +0x114 (param_1[0x45]): m_vec4[2]
    // +0x118 (param_1[0x46]): m_vec5[0]
    // +0x11C (param_1[0x47]): m_vec5[1]
    // +0x120 (param_1[0x48]): m_vec5[2]
    // +0x1E4 (param_1[0x79]): m_pair0[0]
    // +0x1E8 (param_1[0x7A]): m_pair0[1]
    // +0x1EC (param_1[0x7B]): m_pair1[0]
    // +0x1F0 (param_1[0x7C]): m_pair1[1]

    // Constructor
    Player(void* param_2) {
        // Call base class constructor with global data
        Entity::Entity(param_2, g_playerBaseGlobal);

        // Set vtable pointers
        m_vtable = const_cast<void**>(&VTABLE_Player);
        m_baseVtable = const_cast<void**>(&VTABLE_Player_Base);

        // Zero fields at offsets 0xF0–0x104 (six uint32_t)
        reinterpret_cast<uint32_t*>(this)[0x3C] = 0; // offset +0xF0
        reinterpret_cast<uint32_t*>(this)[0x3D] = 0; // +0xF4
        reinterpret_cast<uint32_t*>(this)[0x3E] = 0; // +0xF8
        reinterpret_cast<uint32_t*>(this)[0x3F] = 0; // +0xFC
        reinterpret_cast<uint32_t*>(this)[0x40] = 0; // +0x100
        reinterpret_cast<uint32_t*>(this)[0x41] = 0; // +0x104

        // Zero byte fields at offsets 0x108–0x10A
        *(reinterpret_cast<uint8_t*>(this) + 0x108) = 0; // +0x108
        *(reinterpret_cast<uint8_t*>(this) + 0x109) = 0; // +0x109
        *(reinterpret_cast<uint8_t*>(this) + 0x10A) = 0; // +0x10A

        // Static initialization (e.g., random seed, global counters)
        initializePlayerStatics();

        // Zero vector triple groups
        // Group 1: +0xC0, +0xC4, +0xC8
        reinterpret_cast<uint32_t*>(this)[0x30] = 0;
        reinterpret_cast<uint32_t*>(this)[0x31] = 0;
        reinterpret_cast<uint32_t*>(this)[0x32] = 0;

        // Group 2: +0xCC, +0xD0, +0xD4
        reinterpret_cast<uint32_t*>(this)[0x33] = 0;
        reinterpret_cast<uint32_t*>(this)[0x34] = 0;
        reinterpret_cast<uint32_t*>(this)[0x35] = 0;

        // Group 3: +0xD8, +0xDC, +0xE0
        reinterpret_cast<uint32_t*>(this)[0x36] = 0;
        reinterpret_cast<uint32_t*>(this)[0x37] = 0;
        reinterpret_cast<uint32_t*>(this)[0x38] = 0;

        // Group 4: +0xE4, +0xE8, +0xEC
        reinterpret_cast<uint32_t*>(this)[0x39] = 0;
        reinterpret_cast<uint32_t*>(this)[0x3A] = 0;
        reinterpret_cast<uint32_t*>(this)[0x3B] = 0;

        // Group 5: +0x10C, +0x110, +0x114
        reinterpret_cast<uint32_t*>(this)[0x43] = 0;
        reinterpret_cast<uint32_t*>(this)[0x44] = 0;
        reinterpret_cast<uint32_t*>(this)[0x45] = 0;

        // Group 6: +0x118, +0x11C, +0x120
        reinterpret_cast<uint32_t*>(this)[0x46] = 0;
        reinterpret_cast<uint32_t*>(this)[0x47] = 0;
        reinterpret_cast<uint32_t*>(this)[0x48] = 0;

        // Pair groups (two uint32_t each)
        // Group 7: +0x1E4, +0x1E8
        reinterpret_cast<uint32_t*>(this)[0x79] = 0;
        reinterpret_cast<uint32_t*>(this)[0x7A] = 0;

        // Group 8: +0x1EC, +0x1F0
        reinterpret_cast<uint32_t*>(this)[0x7B] = 0;
        reinterpret_cast<uint32_t*>(this)[0x7C] = 0;
    }
};
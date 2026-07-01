// FUNC_NAME: Entity::Entity
#include <cstdint>

// Forward declarations for external symbols
struct EntityVTable;
extern EntityVTable g_entityVTable;      // PTR_FUN_00d72f34
extern void* g_vtableInterface1;         // PTR_LAB_00d72f24 (offset +0x3C)
extern void* g_vtableInterface2;         // PTR_LAB_00d72f20 (offset +0x48)
extern uint32_t g_entityFlags;           // _DAT_00d5780c

// Global object tracking list (max 32 entries)
static Entity* s_objectList[32];
static int32_t s_objectCount = 0;

// Base class constructor (called at 0x0046c590)
extern void BaseClassConstructor(uint32_t arg);

class Entity {
public:
    // Constructor
    Entity* __thiscall Entity(uint32_t param2); // returns this pointer

    // Virtual table pointer at offset 0x00
    EntityVTable* m_vtable;

    // Fields based on decompiled offsets (all offsets in bytes)
    void* m_interfacePtr1;              // +0x3C (param_1[0xf])
    void* m_interfacePtr2;              // +0x48 (param_1[0x12])
    uint32_t m_field_0x6C;              // +0x6C (param_1[0x1b])
    uint32_t m_field_0x7C;              // +0x7C (param_1[0x1f])
    uint32_t m_field_0x8C;              // +0x8C (param_1[0x23])
    uint32_t m_flags;                   // +0x9C (param_1[0x27])
    uint32_t m_field_0xA0;              // +0xA0 (param_1[0x28]) 
    uint16_t m_short0xA4;               // +0xA4 (short)
    uint16_t m_short0xA6;               // +0xA6 (short)
    uint32_t m_field_0xA8;              // +0xA8 (param_1[0x2a])
    uint32_t m_field_0xAC;              // +0xAC (param_1[0x2b])

    // Debug canary region: four groups of 4 uint32_t each (total 64 bytes)
    // Offsets: 0xB0 (0x2c), 0xB4 (0x2d), 0xB8 (0x2e), 0xBC (0x2f) - first group
    // Then repeat at 0xC0, 0xC4, 0xC8, 0xCC; 0xD0, 0xD4, 0xD8, 0xDC; 0xE0, 0xE4, 0xE8, 0xEC
    uint32_t m_canary[16];              // 16*4 = 64 bytes
};

Entity* __thiscall Entity::Entity(uint32_t param2) {
    // Call base class constructor
    BaseClassConstructor(param2);

    // Set vtable pointer
    m_vtable = &g_entityVTable;

    // Initialize interface pointers
    m_interfacePtr1 = &g_vtableInterface1;   // +0x3C
    m_interfacePtr2 = &g_vtableInterface2;   // +0x48

    // Zero out several fields
    m_field_0x6C = 0;
    m_field_0x7C = 0;
    m_field_0x8C = 0;

    // Set flags from global
    m_flags = g_entityFlags;

    // More zeros
    m_field_0xA0 = 0;
    m_short0xA4 = 0;
    m_short0xA6 = 0;
    m_field_0xA8 = 0;
    m_field_0xAC = 0;

    // Write debug canary values (four repeating patterns)
    // Pattern: 0x91100911, 0xBADBADBA, 0xBEEFBEEF, 0xEAC15A55
    // First group (offset 0xB0-0xBC)
    m_canary[0] = 0x91100911;   // param_1[0x2f]
    m_canary[1] = 0xBADBADBA;   // param_1[0x2c]
    m_canary[2] = 0xBEEFBEEF;   // param_1[0x2d]
    m_canary[3] = 0xEAC15A55;   // param_1[0x2e]

    // Second group (offset 0xC0-0xCC)
    m_canary[4] = 0xBADBADBA;   // param_1[0x30]
    m_canary[5] = 0xBEEFBEEF;   // param_1[0x31]
    m_canary[6] = 0xEAC15A55;   // param_1[0x32]
    m_canary[7] = 0x91100911;   // param_1[0x33]

    // Third group (offset 0xD0-0xDC)
    m_canary[8] = 0xBADBADBA;   // param_1[0x34]
    m_canary[9] = 0xBEEFBEEF;   // param_1[0x35]
    m_canary[10] = 0xEAC15A55;  // param_1[0x36]
    m_canary[11] = 0x91100911;  // param_1[0x37]

    // Fourth group (offset 0xE0-0xEC)
    m_canary[12] = 0xBADBADBA;  // param_1[0x38]
    m_canary[13] = 0xBEEFBEEF;  // param_1[0x39]
    m_canary[14] = 0xEAC15A55;  // param_1[0x3a]
    m_canary[15] = 0x91100911;  // param_1[0x3b]

    // Register this object in the global list (if space available)
    if (s_objectCount < 32) {
        s_objectList[s_objectCount] = this;
        s_objectCount++;
    }

    return this;
}
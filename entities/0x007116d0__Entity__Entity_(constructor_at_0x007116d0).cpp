// FUNC_NAME: Entity::Entity (constructor at 0x007116d0)

class Entity {
public:
    void* vtable;                // +0x00
    uint32_t field_0x04;         // +0x04 (padding?)
    uint32_t field_0x08;         // +0x08
    uint32_t field_0x0C;         // +0x0C
    // offset 0x10..0x8F: 0x80 bytes cleared (likely a buffer or sub-object)
    // ... actual fields from decompiled logic:
    // +0x30: m_pSomePointer
    // +0x34: m_fieldD
    // +0x38: m_pSomePointer2
    // +0x3C: m_fieldF
    // +0x40: byte (flag)
    // +0x48: m_field12
    // +0x4C: m_field13
    // +0x50: m_field14
    // +0x54: m_field15
    // +0x58: m_field16
    // +0x5C: m_field17
    // +0x60: byte (flag, set to 1)
    // +0x68: m_field1A
    // +0x6C: m_field1B
    // +0x74: byte (flag)

    // Globals (set during construction)
    static void* g_SomeGlobal0;   // DAT_00d5ccf8
    static void* g_SomeGlobal1;   // DAT_01205228
    static void* g_EntityVtable;  // PTR_FUN_00d6198c

    __thiscall Entity() {
        // Call base class constructor (FUN_0071e840)
        BaseConstructor();

        // Initialize fields
        *(void**)((uint32_t)this + 0x30) = g_SomeGlobal0;   // param_1[0xc]
        this->vtable = g_EntityVtable;
        *(uint32_t*)((uint32_t)this + 0x0C) = 0;             // param_1[3]
        *(uint32_t*)((uint32_t)this + 0x34) = 0;             // param_1[0xd]
        *(uint32_t*)((uint32_t)this + 0x3C) = 0;             // param_1[0xf]
        *(uint32_t*)((uint32_t)this + 0x48) = 0;             // param_1[0x12]
        *(uint32_t*)((uint32_t)this + 0x4C) = 0;             // param_1[0x13]
        *(uint32_t*)((uint32_t)this + 0x50) = 0;             // param_1[0x14]
        *(uint32_t*)((uint32_t)this + 0x54) = 0;             // param_1[0x15]
        *(uint32_t*)((uint32_t)this + 0x58) = 0;             // param_1[0x16]
        *(uint32_t*)((uint32_t)this + 0x5C) = 0;             // param_1[0x17]
        *(uint8_t*)((uint32_t)this + 0x60) = 1;              // param_1 + 0x18 byte
        *(uint32_t*)((uint32_t)this + 0x68) = 0;             // param_1[0x1a]
        *(uint8_t*)((uint32_t)this + 0x40) = 0;              // param_1 + 0x10 byte
        *(void**)((uint32_t)this + 0x38) = g_SomeGlobal1;    // param_1[0xe]

        // Clear 0x80 bytes starting at offset +0x10 (param_1 + 4)
        memset((void*)((uint32_t)this + 0x10), 0, 0x80);    // FUN_004dde90

        *(uint8_t*)((uint32_t)this + 0x74) = 0;              // param_1 + 0x1d byte
        *(uint32_t*)((uint32_t)this + 0x6C) = 0;             // param_1[0x1b]
    }

private:
    void BaseConstructor();  // placeholder for FUN_0071e840
};
// FUNC_NAME: Entity::Entity

struct Entity {
    char m_initialized; // +0x00
    char _pad1[0x13];   // +0x01 to +0x13
    int m_field_14;     // +0x14
    int m_field_18;     // +0x18
    int m_field_1c;     // +0x1c
    int m_field_20;     // +0x20
    char m_field_24;    // +0x24
};

// External initialization function (possibly engine-wide setup)
extern void __stdcall engineInit(int param);

__thiscall Entity* Entity::Entity(Entity* this) {
    // Mark object as initialized
    this->m_initialized = 1;

    // Engine-level initialization (0 = default or no flags)
    engineInit(0);

    // Zero out distinct fields of the entity
    this->m_field_14 = 0;
    this->m_field_18 = 0;
    this->m_field_1c = 0;
    this->m_field_20 = 0;
    this->m_field_24 = 0;

    return this;
}
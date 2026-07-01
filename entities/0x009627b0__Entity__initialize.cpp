// FUNC_NAME: Entity::initialize
// Function address: 0x009627b0
// Initializes an Entity object, likely called as part of the entity construction process.

Entity* __thiscall Entity::initialize(Entity* this) {
    // Call base class constructor (FUN_008a30d0) – no arguments.
    baseConstructor();

    // Initialization of fields in the range +0x70 to +0x7A
    this->m_unk70 = 0;          // +0x70 (int)
    this->m_unk74 = 0;          // +0x74 (int)
    this->m_unk78 = 0;          // +0x78 (byte)
    this->m_unk79 = 0;          // +0x79 (byte)
    this->m_unk7A = 1;          // +0x7A (byte) – set to 1

    // Call some initialization routine (FUN_008a2dd0) with parameters (0, 3, 0, 0, 0)
    // Possibly sets up a small array or container.
    initContainer(0, 3, 0, 0, 0);

    // Initialize fields in the range +0xCC to +0x100
    this->m_unkCC  = 0;         // +0xCC (int)
    this->m_unkD0  = 0;         // +0xD0 (int)
    this->m_unkD4  = 0;         // +0xD4 (byte)
    this->m_unkD5  = 0;         // +0xD5 (byte)
    this->m_unkD8  = 0;         // +0xD8 (int)
    this->m_unkDC  = 0;         // +0xDC (int)
    this->m_unkE8  = 0;         // +0xE8 (int)
    this->m_unkF0  = 0;         // +0xF0 (int)
    this->m_unkF4  = 0;         // +0xF4 (int)
    this->m_unkF8  = 0;         // +0xF8 (int)
    this->m_unkFC  = 0;         // +0xFC (int)
    this->m_unk100 = 0;         // +0x100 (int)
    this->m_unkE0  = 2;         // +0xE0 (int) – likely element count or type
    this->m_unkE4  = 0x10;      // +0xE4 (int) – likely element size (16)

    return this;
}
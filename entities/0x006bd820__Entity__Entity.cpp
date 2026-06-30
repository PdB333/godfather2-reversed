// FUNC_NAME: Entity::Entity
// Constructor for Entity class (EARS framework base). Sets up vtable and initializes fields.
// Address: 0x006bd820

undefined4* __thiscall Entity::Entity(undefined4* this, undefined4 initParam)
{
    // Call base class constructor (likely Object::Object)
    FUN_0046c590(initParam);

    // Retrieve a global default value (often -1 or 0xFFFFFFFF) from data segment
    undefined4 defaultVal = _DAT_00d5780c;

    // Set vtable pointers (class-specific and base class)
    this[0x14] = &PTR_LAB_00d5e214;          // +0x50 secondary vtable?
    *this = &PTR_FUN_00d5ea9c;               // +0x00 primary vtable
    this[0x0f] = &PTR_LAB_00d5ea8c;          // +0x3c
    this[0x12] = &PTR_LAB_00d5ea88;          // +0x48
    this[0x14] = &PTR_LAB_00d5ea70;          // +0x50 (overwrites previous)
    this[0x15] = 0;                          // +0x54
    this[0x16] = 0;                          // +0x58
    this[0x17] = 0xffffffff;                 // +0x5c
    this[0x1b] = 0;                          // +0x6c
    this[0x1a] = 0;                          // +0x68
    this[0x19] = 0;                          // +0x64
    this[0x18] = 0;                          // +0x60
    this[0x1c] = 0;                          // +0x70
    *(undefined2*)(this + 0x1d) = 0;         // +0x74 (2 bytes)
    *(undefined2*)((int)this + 0x76) = 0;   // +0x76 (2 bytes)
    this[0x1e] = 0;                          // +0x78
    *(undefined2*)(this + 0x1f) = 0;         // +0x7c
    *(undefined2*)((int)this + 0x7e) = 0;   // +0x7e
    this[0x20] = 0;                          // +0x80
    *(undefined2*)(this + 0x21) = 0;         // +0x84
    *(undefined2*)((int)this + 0x86) = 0;   // +0x86
    this[0x34] = 0;                          // +0xd0
    this[0x33] = defaultVal;                 // +0xcc
    this[0x2e] = defaultVal;                 // +0xb8
    this[0x29] = defaultVal;                 // +0xa4
    this[0x24] = defaultVal;                 // +0x90
    this[0x27] = 0;                          // +0x9c
    this[0x28] = 0;                          // +0xa0
    this[0x26] = 0;                          // +0x98
    this[0x25] = 0;                          // +0x94
    this[0x2b] = 0;                          // +0xac
    this[0x2d] = 0;                          // +0xb4
    this[0x2c] = 0;                          // +0xb0
    this[0x2a] = 0;                          // +0xa8
    this[0x2f] = 0;                          // +0xbc
    this[0x32] = 0;                          // +0xc8
    this[0x31] = 0;                          // +0xc4
    this[0x30] = 0;                          // +0xc0

    // If a global data pointer is set, copy a large block (0x8000 bytes) into member buffer at +0x3c
    if (DAT_0120e93c != 0) {
        FUN_00408900(this + 0x0f, &DAT_0120e93c, 0x8000);  // likely memcpy of asset data
    }

    return this;
}
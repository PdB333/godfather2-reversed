// FUNC_NAME: Building::Building
undefined4* __thiscall Building::Building(undefined4* this, undefined4 param_2)
{
    // Call base class constructor (e.g., Entity::Entity)
    FUN_00473840(param_2);

    // Set vtable pointers for multiple inheritance bases
    this[0] = &PTR_FUN_00d5f228;               // +0x00 main vtable
    this[0xf] = &PTR_LAB_00d5f214;             // +0x3c
    this[0x12] = &PTR_LAB_00d5f210;            // +0x48
    this[0x14] = &PTR_LAB_00d5f20c;            // +0x50

    // Call static initialization
    FUN_00473750();

    // Zero out building-specific fields (likely flags, timers, etc.)
    this[0x2d] = 0;                            // +0xb4
    *(short*)(this + 0x2e) = 0;                // +0xb8
    *(short*)((int)this + 0xba) = 0;           // +0xba
    this[0x2f] = 0;                            // +0xbc
    *(short*)(this + 0x30) = 0;                // +0xc0
    *(short*)((int)this + 0xc2) = 0;           // +0xc2
    this[0x32] = 0;                            // +0xc8
    this[0x33] = 0;                            // +0xcc
    this[0x34] = 0;                            // +0xd0
    this[0x35] = 0;                            // +0xd4

    // Additional constructor chain
    FUN_006cf1a0();
    FUN_008a0d80(this);

    return this;
}
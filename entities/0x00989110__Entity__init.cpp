// FUNC_NAME: Entity::init
// Address: 0x00989110
// Initialization routine: sets an internal flag, builds a temporary structure from a global, then calls a virtual method (likely postInit or onCreate)
void __thiscall Entity::init(void)
{
    // Set initialization flag at offset +0x16 to true
    *(uint8_t*)((uintptr_t)this + 0x16) = 1;

    // Temporary stack data built from global DAT_011302c8 (likely a pointer or resource handle)
    struct InitData {
        uint32_t data0; // +0x0
        uint32_t data4; // +0x4
        uint8_t  data8; // +0x8
    } localInit;
    localInit.data0 = DAT_011302c8;
    localInit.data4 = 0;
    localInit.data8 = 0;

    // Process the temporary data (possibly to copy or validate)
    FUN_00408a00(&localInit, 0);

    // Call virtual function at vtable offset 0x2c (index 11)
    // Vtable pointer is at offset 0 of the object
    (*(void(__thiscall**)(void*))(*(uint32_t*)this + 0x2c))(this);
}
// FUNC_NAME: GameManager::~GameManager
undefined4 * __thiscall GameManager::destructor(GameManager *this, byte deallocFlag)
{
    // Set vtable to base class destructor vtable
    *this = &PTR_FUN_00d8bed8;                        // +0x00
    // Set another vtable pointer (likely for a contained subobject)
    this[4] = &PTR_LAB_00d8beb0;                      // +0x10
    // Set pointer to a function table or serialization data
    this[0x13] = &PTR_LAB_00d8beac;                   // +0x4C

    // If a member at offset 0x5C is non-null, release it
    if (this[0x17] != (void *)0)                      // +0x5C
    {
        FUN_009c8f10(this[0x17]);                     // release contained object
    }

    // Switch to a different base vtable (likely final destructor variant)
    this[0x13] = &PTR_LAB_00d8bea8;                   // +0x4C

    // Clear global static flag
    g_someGlobal = 0;                                 // DAT_01130594

    // Perform common cleanup (e.g., shutting down subsystems)
    commonCleanup();

    // If deallocation flag is set, free the object's memory
    if ((deallocFlag & 1) != 0)
    {
        deallocateMemory(this);                       // e.g., operator delete
    }

    return this;
}
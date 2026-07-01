// FUNC_NAME: SomeManager::SomeManager
// Address: 0x00911bf0
// Role: Constructor for a manager class with multiple base classes (vtable at +0x00, +0x04, +0x13)
// Sets a global flag to 0, calls base initialization, and optionally deallocates if param_2 & 1

undefined4* __thiscall SomeManager::SomeManager(undefined4* this, byte createFlag)
{
    // Set vtable pointers for multiple inheritance
    *this = &PTR_FUN_00d84018;          // Primary vtable (offset +0x00)
    this[4] = &PTR_LAB_00d83ff4;        // First base class vtable (offset +0x10)
    this[0x13] = &PTR_LAB_00d83fec;     // Second base class vtable (offset +0x4C)
    
    // Initialize global singleton flag
    g_someManagerInitialized = 0;       // DAT_0112fe08
    
    // Call base class initialization
    initializeBase();                   // FUN_005c16e0
    
    // If createFlag has bit 0 set, destroy this object (deallocation)
    if ((createFlag & 1) != 0) {
        deallocateObject(this);         // FUN_005c4480
    }
    
    return this;
}
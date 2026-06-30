// FUNC_NAME: CGameManager::CGameManager
// Address: 0x469660
// Role: Constructor for the game manager singleton. Sets up vtable pointers for base and derived class,
//       calls base class constructor, resets a global singleton flag to 0, and optionally performs
//       dynamic allocation setup if the object was heap-allocated (bit 0 of isAllocated set).

// Class structure offsets:
// +0x00: vtable pointer (main)
// +0x04: vtable pointer (secondary, for multiple inheritance)
// Global: _DAT_01223478 - singleton creation flag

undefined4* __thiscall CGameManager::CGameManager(byte isAllocated)
{
    // Set base class vtables (required before calling base constructor)
    *(void**)this = (void*)&PTR_FUN_00e320ac;          // +0x00: base main vtable
    *(void**)((int)this + 4) = (void*)&PTR_LAB_00e320b8; // +0x04: base secondary vtable

    // Call base class constructor (likely from a parent like EARSObject)
    CGameManager::invokeBaseConstructor(this); // FUN_0043e380

    // Override vtable pointers with derived class versions
    *(void**)((int)this + 4) = (void*)&PTR_LAB_00e320bc; // +0x04: derived secondary vtable
    g_globalSingletonCreated = 0;                        // _DAT_01223478: reset flag to 0

    // Set final derived class main vtable
    *(void**)this = (void*)&PTR_LAB_00e30ea0;          // +0x00: derived main vtable

    // If the object was dynamically allocated (usually via operator new), perform extra setup
    if (isAllocated & 1) {
        CGameManager::handleDynamicAllocation(this); // FUN_009c8eb0
    }

    return this;
}
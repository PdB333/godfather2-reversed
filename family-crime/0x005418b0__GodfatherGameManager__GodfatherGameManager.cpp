// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x005418b0
// Constructor for GodfatherGameManager. Allocates main object memory via aligned pool, sets up virtual function tables for multiple inheritance,
// initializes embedded sub-objects, and copies global configuration data.

undefined4* __thiscall GodfatherGameManager::GodfatherGameManager(undefined4* this, undefined4 allocSizeOrPool) {
    undefined4* subObject;

    // Allocate main object memory from pool with 0x4000 alignment (likely a page or large block)
    allocateFromPool(allocSizeOrPool, 0x4000);

    // Set primary vtable for the class itself
    *this = &PTR_FUN_00e392a0;

    // Set vtable pointers for embedded base classes or interface objects
    this[0x0F] = &PTR_LAB_00e393f8;   // +0x3C
    this[0x12] = &PTR_LAB_00e39408;   // +0x48
    this[0x14] = &PTR_LAB_00e3940c;   // +0x50
    this[0x15] = &PTR_LAB_00e39410;   // +0x54
    this[0x16] = &PTR_LAB_00e39470;   // +0x58

    // Global one-time initialization (e.g., static members, engine subsystems)
    globalInit();

    // Zero out key fields
    this[0x98] = 0;  // +0x260 – some large offset, possibly a pointer or count
    this[0x60] = 0;  // +0x180 – another field

    // Allocate a sub-object of size 0x14 (20 bytes) – e.g., a manager for input, AI, etc.
    subObject = (undefined4*) allocateMemory(0x14);
    if (subObject != (undefined4*)0x0) {
        // Initialize sub-object's own virtual tables (multiple inheritance)
        subObject[1] = &PTR_LAB_00dc3dd4;  // +0x04 vtable1
        subObject[2] = &PTR_LAB_00e39260;  // +0x08 vtable2
        *subObject = &PTR_LAB_00e3926c;    // +0x00 primary vtable
        subObject[1] = &PTR_LAB_00e39280;  // Note: overwritten – likely decompilation artifact or additional base
        subObject[2] = &PTR_LAB_00e39294;  // Overwritten again
        subObject[3] = this;               // +0x0C store pointer back to parent
        subObject[4] = 0;                  // +0x10 some zeroed field
    }
    this[0x99] = subObject;  // +0x264 store sub-object pointer

    // If global static data is present, copy it into the embedded object at offset +0x3C
    if (DAT_0120e93c != 0) {
        copyData(this + 0x0F, &DAT_0120e93c);  // +0x3C is the base of that embedded object
    }

    return this;
}
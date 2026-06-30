// FUNC_NAME: Entity::~Entity

// Function address: 0x006f2ee0
// Destructor for base entity class. Sets vtable pointers for multiple inheritance,
// calls base class destructors, cleans up member arrays, and checks for a global singleton.
// Offsets: +0x00 vtable (base), +0x3C vtable (base1), +0x48 vtable (base2)
// +0x58 to +0x70: member array pointers (4 arrays)
// +0x7C: pointer member1 (+0x1f*4)
// +0x84: pointer member2 (+0x21*4)
// +0x8C: byte flags (+0x23*4, bit 0x10 used)

void __thiscall Entity::~Entity(Entity *this)
{
    char flagByte;
    
    // Set vtable pointers to "destructor" tables to prevent virtual calls during destruction
    this->vtable = &vtable_Entity_00d605f0;          // +0x00
    *(void **)((int)this + 0x3C) = &vtable_Base1_00d605e0;  // +0x3C
    *(void **)((int)this + 0x48) = &vtable_Base2_00d605dc;  // +0x48
    
    // Call base class destructors (sub-objects at fixed offsets)
    base1::~base1((Base1 *)((int)this + 0x00));     // FUN_006fc560
    base2::~base2((Base2 *)((int)this + 0x00));     // FUN_006f0ea0
    base3::~base3((Base3 *)((int)this + 0x00));     // FUN_006fbca0
    
    // Handle global singleton (probably a log manager or asset cache)
    if (checkGlobalIsActive(&g_someGlobalInstance)) {
        releaseGlobal(&g_someGlobalInstance);       // FUN_004086d0
    }
    
    // Release and clear four member arrays (likely containers or lists)
    releaseArray((ArrayHeader *)((int)this + 0x58));   // +0x16*4
    clearArray((ArrayHeader *)((int)this + 0x58));
    
    releaseArray((ArrayHeader *)((int)this + 0x60));   // +0x18*4
    clearArray((ArrayHeader *)((int)this + 0x60));
    
    releaseArray((ArrayHeader *)((int)this + 0x68));   // +0x1a*4
    clearArray((ArrayHeader *)((int)this + 0x68));
    
    releaseArray((ArrayHeader *)((int)this + 0x70));   // +0x1c*4
    clearArray((ArrayHeader *)((int)this + 0x70));
    
    // Check flag at offset 0x8C (bit 4) and call a special handler if set
    flagByte = *(byte *)((int)this + 0x8C);
    if ((flagByte & 0x10) != 0) {
        handleFlaggedAction(0);                   // FUN_006f0910
    }
    
    // Delete two optional member objects
    if (*(void **)((int)this + 0x84) != 0) {     // +0x21*4
        deleteObject((void **)((int)this + 0x84)); // FUN_004daf90
    }
    if (*(void **)((int)this + 0x7C) != 0) {     // +0x1f*4
        deleteObject((void **)((int)this + 0x7C));
    }
    
    // Final global cleanup (probably de-registers from the entity system)
    finalCleanupGlobal();                         // FUN_0046c640
    
    return;
}
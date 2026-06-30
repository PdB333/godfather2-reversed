// FUNC_NAME: EARS::GhostObject::createInstance
EARS::GhostObject* EARS::GhostObject::createInstance(EARS::Context* context) {
    EARS::MemoryManager* memMgr = EARS::MemoryManager::instance();
    
    // Allocation parameters: size=0x60, alignment=0x10, flags=2
    EARS::AllocParams params;
    params.flags = 2;
    params.alignment = 0x10;
    params.unknown = 0;
    
    EARS::GhostObject* obj = (EARS::GhostObject*)memMgr->allocate(0x60, &params);
    if (obj) {
        // Base class initialization (calls FUN_00473950, likely initBase)
        obj->initBase(context);
        
        // Set up vtable pointers for multiple inheritance
        // +0x0: primary vtable
        obj->vftable = &EARS::GhostObject_vtable;
        // +0x8: secondary vtable (possibly for a base interface)
        obj->secondaryVftable = &EARS::GhostObject_secondary_vtable;
    }
    return obj;
}
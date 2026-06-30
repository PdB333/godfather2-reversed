// FUNC_NAME: Entity::registerWithManager
void Entity::registerWithManager() {
    // Get manager singleton (e.g., some global component manager)
    void* manager = (void*)FUN_009c8f80();
    
    // Configuration parameters for the registration
    // Structure: [ type (2), size (0x10), flags (0) ]
    int config[3];
    config[0] = 2;      // +0x00: type identifier
    config[1] = 0x10;   // +0x04: size or count
    config[2] = 0;      // +0x08: flags
    
    // Call manager's first virtual function with this object and config
    // vtable entry 0: likely RegisterObject(Entity* obj, Config* params)
    (*(void (__thiscall**)(void*, void*, void*))manager)[0](manager, this, config);
}
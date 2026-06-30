// FUNC_NAME: GameSystem::GameSystem
GameSystem* __fastcall GameSystem::GameSystem(GameSystem* this) {
    // Base class constructor call
    baseConstructor();
    
    // Initialize vtable pointer at offset 0x08 (this[2])
    this->vtable2 = &PTR_LAB_00d60708;     // Initial vtable2
    // Global pointer to this instance
    g_pGameSystem = this;                   // DAT_01129974
    
    // Set primary vtable (offset 0x00)
    this->vtable = &PTR_FUN_00d60710;      // Primary vtable
    
    // Overwrite vtable2 with a different pointer
    this->vtable2 = &PTR_LAB_00d6070c;     // Updated vtable2
    
    // Initialize field at offset 0x0C (this[3])
    this->someField = 0;                    // e.g., m_pSubSystem
    
    // Static registration / global hook (arg1 = 1, arg2 = address of static data)
    registerGlobal(&DAT_00d6071c, 1);       // FUN_0049c6e0
    
    return this;
}
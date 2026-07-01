// FUNC_NAME: GameManager::GameManager
void __thiscall GameManager::GameManager(GameManager* this)
{
    // Set initial vtable pointers (base class vtables)
    this->vtable0 = &PTR_FUN_00d69864;          // +0x00: primary vtable
    this->vtable4 = &PTR_LAB_00d69854;          // +0x04: secondary vtable
    this->vtable16 = &PTR_LAB_00d69838;         // +0x10: another vtable (offset 0x10? Actually param_1[4] is offset 0x10)

    // Initialize global singletons/managers
    initializeSingleton(&DAT_0112fc60);          // e.g., AudioManager
    shutdownSingleton(&DAT_0112fc60);            // Note: shutdown after init? Possibly reinit
    initializeSingleton(&DAT_0112dcf4);          // e.g., NetworkManager
    initSubsystem();                             // FUN_00786bc0 - likely subsystem init
    initializeSingleton(&DAT_012069c4);          // e.g., InputManager
    initializeSingleton(&DAT_012069d4);          // e.g., RenderManager
    initializeSingleton(&DAT_0112af78);          // e.g., PhysicsManager
    shutdownSingleton(&DAT_0112af78);
    initializeSingleton(&DAT_0112af88);          // e.g., EntityManager
    shutdownSingleton(&DAT_0112af88);
    initializeSingleton(&DAT_0112af80);          // e.g., ScriptManager
    shutdownSingleton(&DAT_0112af80);

    // Construct sub-object at offset 0xb1a (2842 bytes)
    constructSubObject(this + 0xb1a);            // FUN_0043e380 - placement new or init

    // Release previous sub-object if present
    if (this->field_0xb1f != 0) {               // +0xb1f*4 = offset 0xb1f*4? Actually param_1[0xb1f] is a pointer at offset 0xb1f*4
        releaseSubObject(this->field_0xb1f);    // FUN_009c8f10
    }

    // Set vtable for sub-object at 0xb1a
    this->subObjectVtable = &PTR_LAB_00e30ea0;  // +0xb1a

    // Setup additional vtables for interfaces
    setupVtable();                               // FUN_004abf00
    this->interfaceVtable1 = &PTR___purecall_00e30fac; // +0xb10
    setupVtable();                               // FUN_004abf00
    this->interfaceVtable2 = &PTR___purecall_00e30fac; // +0x645

    // Final initialization
    finalizeInit();                              // FUN_004083d0

    // Override primary vtable to final version
    this->vtable0 = &PTR_LAB_00d69804;          // +0x00: final vtable

    // Mark global initialization complete
    g_initialized = 0;                          // DAT_0112aa1c = 0
}
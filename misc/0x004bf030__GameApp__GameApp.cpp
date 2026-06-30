// FUNC_NAME: GameApp::GameApp
void __fastcall GameApp::GameApp(GameApp* this) // __fastcall with this in ECX (treated as __thiscall)
{
    // Set vtable pointers for this object (multiple inheritance)
    *this->vtable = &GameApp_vtable;        // +0x00: primary vtable pointer (PTR_FUN_00e35de8)
    *(void**)((char*)this + 4) = &BaseClass_vtable; // +0x04: secondary vtable pointer (PTR_LAB_00e35e80)
    *(void**)((char*)this + 0xD8) = &AnotherBase_vtable; // +0xD8: third vtable pointer (PTR_LAB_00e35e84)

    // Initialize global engine subsystems
    AudioManager::constructor(&g_audioSystem);     // 0x0120ea74
    AudioManager::init(&g_audioSystem);            // 0x0120ea74 (same object, second call)
    RenderManager::init(&g_renderer);              // 0x01218060
    PhysicsManager::init(&g_physics);              // 0x01218068
    InputManager::init(&g_input);                  // 0x01218070
    NetworkManager::init(&g_network);              // 0x01218058

    // Global engine startup and finalization
    EngineCore::startAllSystems();                 // FUN_004083d0
    EngineCore::initializeWindow();                // FUN_00568000
}
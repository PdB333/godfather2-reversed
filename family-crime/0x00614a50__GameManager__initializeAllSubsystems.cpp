// FUNC_NAME: GameManager::initializeAllSubsystems
void GameManager::initializeAllSubsystems() {
    // Initialize audio system with global audio manager and audio data pointers
    AudioSystem_Init(&g_AudioManager, &g_AudioState); // DAT_011f6b30, DAT_011f6ab0

    // Initialize the physics engine (called from FUN_00417560)
    PhysicsEngine_Init();

    // Initialize the rendering subsystem (FUN_00611f70)
    RenderingEngine_Init();

    // Initialize the network layer (FUN_00612130)
    NetworkEngine_Init();

    // Initialize the input system with the global input manager (FUN_00612210, DAT_011f6b70)
    InputSystem_Init(&g_InputManager);
}
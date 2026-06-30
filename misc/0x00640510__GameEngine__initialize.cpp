// FUNC_NAME: GameEngine::initialize
// Address: 0x00640510
// Role: Initializes two core subsystems during engine startup.
void GameEngine::initialize() {
    // Initialize the rendering subsystem (callee at 0x0063fad0)
    initRenderSystem();
    // Initialize the physics or simulation subsystem (callee at 0x00642ec0)
    initPhysicsSystem();
}
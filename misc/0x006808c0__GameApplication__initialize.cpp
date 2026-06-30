// FUNC_NAME: GameApplication::initialize
GameApplication* __thiscall GameApplication::initialize(GameApplication* this, undefined4 windowHandle)
{
    undefined4 displayHandle;
    int featureCheck;

    // Store the platform window/application handle (likely HWND or HINSTANCE)
    *(undefined4*)this = windowHandle;

    // Initialize underlying graphics memory pool or buffer size (0x200 = 512?)
    GraphicsMemoryPool::allocate(0x200, 5);
    // Set depth buffer or render target parameters
    RenderTarget::setDepthStencil(0x200, 1);
    // Initialize core subsystems (input, audio, etc.)
    SubsystemManager::initCore();
    // Initialize networking layer (EARS net session)
    NetSession::startup();
    // Reset the game timer to zero
    GameTimer::reset(0);

    // Obtain current display adapter info
    displayHandle = DisplayDevice::getPrimaryMonitor();
    featureCheck = DisplayDevice::getResolutionInfo(displayHandle);
    // Set the backbuffer resolution from the monitor's native resolution (stored at +2 and +4)
    Renderer::setResolution(*(uint16*)(featureCheck + 2), *(uint16*)(featureCheck + 4));

    // Check for optional features and conditionally initialize subsystems
    featureCheck = FeatureManager::isEnabled(0x54);   // e.g., "HighQualityParticles"
    if (featureCheck != 0) {
        // Create a particle system with parameters (3,1)
        displayHandle = ParticleFactory::create(3, 1);
        ParticleSystem::initialize(displayHandle, 3, 1);
    }

    // Finalize render state setup (depth, stencil, blending)
    RenderState::applyDefaults();

    featureCheck = FeatureManager::isEnabled(0x20);   // e.g., "PostProcessBlur"
    if (featureCheck != 0) {
        PostProcessManager::initBloom();
    }

    featureCheck = FeatureManager::isEnabled(0x18);   // e.g., "ShadowMap"
    if (featureCheck != 0) {
        ShadowRenderer::initShadowMaps();
    }

    featureCheck = FeatureManager::isEnabled(0x80);   // e.g., "DynamicLighting"
    if (featureCheck != 0) {
        LightManager::initLightBuffers();
    }

    featureCheck = FeatureManager::isEnabled(0x40);   // e.g., "WaterReflections"
    if (featureCheck != 0) {
        WaterRenderer::initWaterSimulation();
    }

    // Mark the application as active and run final initialization hooks
    GameLoop::setActive(1);
    GameState::finalizeInitialization();

    return this;
}
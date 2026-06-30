// FUNC_NAME: initializeCoreSystems

void initializeCoreSystems(void)
{
    // Initialize sound/audio subsystem
    initializeSoundSystem(); // 0x004abd90
    // Initialize rendering/graphics subsystem
    initializeRenderingSystem(); // 0x004abc50
}
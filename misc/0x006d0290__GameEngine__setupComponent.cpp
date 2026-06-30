// FUNC_NAME: GameEngine::setupComponent
// Function address: 0x006d0290
// Role: Calls a virtual method on a singleton manager to initialize a component with a configuration (type=2, size=16, flags=0)
// The manager is obtained via FUN_009c8f80() (likely SystemManager::getInstance or similar)

void GameEngine::setupComponent(CComponent* component) {
    // Get the global manager instance
    Manager* manager = (Manager*)FUN_009c8f80();  // Possibly SystemManager* or ConfigManager*

    // Configuration structure: { type, size, flags }
    struct Config {
        int type;   // +0x00
        int size;   // +0x04
        int flags;  // +0x08
    } config = {2, 0x10, 0};

    // Call vtable function at offset 0 (first virtual method) on manager,
    // passing the component and the config pointer.
    // The function likely initializes or registers the component.
    (*(void (__thiscall*)(Manager*, CComponent*, Config*))manager->vtable[0])(manager, component, &config);
}
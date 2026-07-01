// FUNC_NAME: Entity::initialize
// Function at 0x0094fa40: Initializes base entity (calls system init and registers component at +0x54)
void __thiscall Entity::initialize(Entity *this) {
    // Global system initialization (likely static engine setup)
    ::initializeGlobalSystem(); // FUN_005c1740

    // Register a component (e.g., IComponent*) located at this+0x54
    // Args: component manager global, component pointer, unknown flags (0,0,0,1)
    g_ComponentManager->attachComponent(this->componentPtr, 0, 0, 0, 1); // FUN_005c01d0
}
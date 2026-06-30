// FUNC_NAME: EntityManager::disableComponent
// Address: 0x006f9af0
// This function looks up a component from an entity handle and disables it (sets enabled to false).
// The component pointer is obtained via getComponent(handle), then setEnabled(component, 0) is called.
void EntityManager::disableComponent(EntityHandle handle) {
    int component = getComponent(handle); // 0x004025a0 - returns component pointer or 0
    if (component != 0) {
        setComponentEnabled(component, 0); // 0x004048c0 - set enabled = false
    }
}
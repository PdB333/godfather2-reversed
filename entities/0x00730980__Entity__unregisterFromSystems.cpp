// FUNC_NAME: Entity::unregisterFromSystems
void Entity::unregisterFromSystems()
{
    // Get pointers to two global managers (e.g., simulation and rendering)
    void* simManager = getSimulationManager();       // FUN_0072d450
    int objectHandle = getObjectHandle(this->m_objectId); // FUN_008c7670 - retrieves an internal handle

    if (simManager != nullptr) {
        unregisterFromSimulation(simManager, this); // FUN_00894c40
    }
    if (objectHandle != 0) {
        unregisterFromObjectManager(objectHandle); // FUN_00894c90
    }
}
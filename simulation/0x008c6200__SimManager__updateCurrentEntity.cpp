// FUNC_NAME: SimManager::updateCurrentEntity

void SimManager::updateCurrentEntity()
{
    // Retrieve the current entity pointer from internal state (likely an iterator or index)
    // FUN_008bee20: returns SimEntity* or nullptr
    SimEntity* entity = this->getActiveEntity();

    if (entity != nullptr) {
        // Perform per-frame update on the entity (e.g., AI, physics, animation)
        // FUN_008c5130: entity->update()
        entity->update();
    }
}
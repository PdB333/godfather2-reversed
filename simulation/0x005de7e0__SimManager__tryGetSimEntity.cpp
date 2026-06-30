// FUNC_NAME: SimManager::tryGetSimEntity
// Function address: 0x005de7e0
// Attempts to retrieve a sim entity by ID if the manager is in a valid state.
// Returns true on success and fills outEntity, false otherwise.

bool SimManager::tryGetSimEntity(uint32_t entityId, SimEntity*& outEntity)
{
    if (this->isValid()) {
        outEntity = getEntityById(entityId);
        return true;
    }
    return false;
}
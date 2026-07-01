// FUNC_NAME: EntityManager::processFoundEntity
void EntityManager::processFoundEntity() {
    int foundIndex = findEntityIndex();  // Searches for an entity matching criteria; returns index or -1
    if (foundIndex >= 0) {
        activateEntityByIndex(foundIndex);  // Performs action on the found entity (e.g., spawn, remove, update)
    }
}
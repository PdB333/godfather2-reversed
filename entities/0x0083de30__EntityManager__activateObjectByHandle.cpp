// FUNC_NAME: EntityManager::activateObjectByHandle
void EntityManager::activateObjectByHandle(int objectHandle) {
    int objectIndex = findObjectIndex(objectHandle);
    if (objectIndex >= 0) {
        processObjectByIndex(objectIndex);
    }
    return;
}
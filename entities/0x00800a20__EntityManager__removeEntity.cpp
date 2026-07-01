// FUNC_NAME: EntityManager::removeEntity

void EntityManager::removeEntity(int entityId)
{
    if (entityId == 0) {
        return;
    }

    bool isGameActive = isGameRunning(); // FUN_00481620
    if (isGameActive) {
        removeEntityFromWorld(entityId); // FUN_00704360
    }

    int* currentObjectPtr = reinterpret_cast<int*>(this->m_pCurrentObject); // +0x74c

    // Compute the ID of the currently tracked object. 
    // The pointer's value minus 0x48 yields the actual entity ID (handle).
    int currentObjectId;
    if (this->m_pCurrentObject == 0) {
        currentObjectId = 0;
    } else {
        currentObjectId = this->m_pCurrentObject - 0x48;
    }

    if (entityId == currentObjectId) {
        if (this->m_pCurrentObject != 0) {
            deleteObject(this->m_pCurrentObject); // FUN_004daf90
            this->m_pCurrentObject = 0;
        }
        logDebugMessage(10); // FUN_007f6420
    }
}
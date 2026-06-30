// FUNC_NAME: Entity::setupDataPointer
void Entity::setupDataPointer() {
    // Retrieve data pointer from the entity data manager (helper function at 0x006808c0)
    void* pData = EntityDataManager::getData(this); // FUN_006808c0
    this->dataPtr = pData; // +0x20
}
// FUNC_NAME: EntityManager::isPointInArea
bool EntityManager::isPointInArea(int entityIndex) {
    float posX; // local_20
    float posY; // local_1c
    float posZ; // local_18

    // Retrieve world position (fills posX, posY, posZ via pointer to first element)
    // Returns pointer to entity data for reading additional fields
    EntityData* entityData = this->getEntityWorldPosition(entityIndex, &posX);

    // Check against axis-aligned bounding box
    // Global bounds: g_minBound (0x00e44710), g_maxBound (0x00e445a4)
    // Z offset from entity data at +0x20 (float)
    if ((((g_minBound <= posX) && (posX <= g_maxBound)) &&
         (g_minBound <= posY)) &&
        (((posY <= g_maxBound) &&
          ((entityData->field_0x20 - g_zBaseOffset) <= posZ)) &&
         (posZ <= g_maxBound))) {
        return true;
    }
    return false;
}
// FUNC_NAME: EntityManager::getEntityPosition
undefined1 __thiscall EntityManager::getEntityPosition(EntityManager *this, Vector3 *outPosition) {
    Entity *entity;
    int iVar1;

    // First try: use entity type from global DAT_0113105c
    if (this->entityType != 0) {
        entity = getEntityByType(DAT_0113105c); // get entity by global type ID
        if (entity != 0 && ((entity->flags1 >> 2) & 1) != 0) {
            if (isEntityActive() == 0) { // check if entity is active
                return 0;
            }
            // Get position from player manager's data
            PlayerManager *playerMgr = getPlayerManager();
            *outPosition = playerMgr->position; // copy 12 bytes (3 floats) from +0x30,+0x38
            // Note: offset 0x30 = first 8 bytes (2 floats), offset 0x38 = next 4 bytes (1 float)
            return 1;
        }
    }

    // Second try: use entity type from global DAT_01131064
    if (this->entityType != 0) {
        entity = getEntityByType(DAT_01131064);
        if (entity != 0 && ((entity->flags2 & 1) != 0) && (entity->flags2 >= 0)) {
            *outPosition = entity->transform; // copy 12 bytes from +0x18,+0x20
            // offset 0x18 = first 8 bytes, 0x20 = last 4 bytes
            return 1;
        }
    }

    return 0;
}
// FUNC_NAME: EntityManager::createEntity
void EntityManager::createEntity(EntityCreateParams* params) {
    // Check if game is active
    if (!isGameActive()) {
        processNext();
        return;
    }

    // Allocate memory for the entity (size 0x68)
    Entity* entity = (Entity*)customAlloc(0x68);
    if (entity != nullptr) {
        entity = constructEntity(entity, params->typeId);
        // Set field values from params (offsets from entity base)
        entity->field_0x3c = params->field3;  // +0x3c
        entity->field_0x40 = params->field4;  // +0x40
        entity->field_0x44 = params->field5;  // +0x44
        entity->field_0x48 = params->field6;  // +0x48
        entity->field_0x4c = params->field7;  // +0x4c
        entity->field_0x50 = params->field8;  // +0x50
        entity->field_0x54 = params->field9;  // +0x54
        entity->field_0x58 = params->field10; // +0x58 (byte)
        // Register the entity in the game world
        registerEntity(entity);
        // Process the parameter block (e.g., for additional setup)
        processEntityParams(params);
    }
    // Post-creation step
    processNext();
}
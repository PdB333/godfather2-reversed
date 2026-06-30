// FUNC_NAME: Entity::checkAndProcessUpdate
void Entity::checkAndProcessUpdate(Entity* entity, int updateData) {
    int isReady = isEntityReady(entity);   // FUN_006f9240 - checks if entity is initialized/ready
    if (isReady == 0) {
        int isActive = isEntityActive(entity); // FUN_006f9300 - checks if entity is active in update loop
        if (isActive == 0) {
            goto skipProcess; // Neither ready nor active: skip processing
        }
    }
    // Entity is ready or active: apply the update data
    processEntityUpdate(updateData); // FUN_006f9670 - applies the update (e.g., input, delta, event)
skipProcess:
    finalizeEntityUpdate(); // FUN_0072cf40 - post-update cleanup (e.g., profiling marker, sync)
    return;
}
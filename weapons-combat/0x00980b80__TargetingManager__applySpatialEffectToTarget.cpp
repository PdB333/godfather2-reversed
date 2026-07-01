// FUNC_NAME: TargetingManager::applySpatialEffectToTarget
void TargetingManager::applySpatialEffectToTarget(int targetHandle)
{
    // Check if handle is valid
    if (targetHandle == 0) {
        return;
    }

    // Retrieve the entity object from the handle (e.g., SimObject pointer)
    Entity* targetEntity = getEntityFromHandle(targetHandle);
    if (targetEntity == 0) {
        return;
    }

    // Check if the entity is alive or valid for the effect (e.g., isSentient, isTargetable)
    if (!isEntityValid(targetEntity)) {
        return;
    }

    // Allocate a temporary 3D position vector (initialized to zero)
    Vector3 targetPosition = { 0.0f, 0.0f, 0.0f };

    // Fill position from the entity's world position
    getEntityPosition(&targetPosition);

    // Get magnitude (distance from origin) for effect calculation
    float distance = getPositionMagnitude(&targetPosition);

    // Apply the spatial effect using the distance and position reference
    applySpatialEffect(distance, &targetPosition);

    return;
}
// FUNC_NAME: TargetingManager::checkLineOfSight
bool TargetingManager::checkLineOfSight(Vector3* from, Vector3* to, uint32_t filterFlags, int32_t unknownParam5, int32_t randomizeSeed, uint32_t flags) {
    Vector3 localStart;
    Vector3 localEnd; // actually local_100, local_108, local_fc, local_f8 but treat as separate
    // Actually the decompile uses a 4-float array local_118, but we'll use Vector3 and a float for random offset.
    float local_118[4];
    float local_108;
    float local_104;
    float local_100;
    float local_fc;
    float local_f8;
    float local_f4;
    char collisionOutput[80]; // local_f0
    char tempPrefix[4]; // local_a0
    int32_t hitEntityId; // local_40

    local_118[2] = from->x;
    local_118[3] = from->y;
    local_108 = from->z;
    local_100 = to->x;
    local_fc = to->z;
    local_f8 = to->y;
    local_104 = gEpsilon; // _DAT_00d5780c, likely 0.0f
    local_f4 = gEpsilon;

    int32_t randomCount = 0;
    if (randomizeSeed != 0) {
        local_118[0] = (float)getRandomFloat(); // FUN_0043b490
        randomCount = 1;
    }

    int32_t extraRandom = getExtraRandomBool(); // FUN_007ff880
    if (extraRandom != 0) {
        float extraFloat = (float)getRandomFloat();
        local_118[randomCount] = extraFloat;
        randomCount++;
    }

    performRaycast(&local_108, &local_118[2], filterFlags, 0x01000001, local_118, randomCount); // FUN_005425d0

    // Build collision result string? (likely unused)
    initCollisionOutput(collisionOutput, 1); // FUN_0054b2c0
    formatCollisionString(collisionOutput, tempPrefix); // FUN_009e5ed0, sets hitEntityId via output

    bool isHit = (hitEntityId == 0); // bVar7

    if (flags == 0) {
        return isHit; // no flags, just return whether something was hit
    }

    if (hitEntityId == 0) {
        return isHit;
    }

    // We hit something, get the entity
    Entity* hitEntity = getEntityById(hitEntityId); // FUN_004afca0
    if (hitEntity == nullptr || *(char*)(hitEntity + 0x15e) < 0) {
        // Entity is invalid or flag at offset +0x15e (maybe dead/destroyed)
        if ((flags & 4) == 0) {
            return isHit;
        }
        // Check distance to interpolated point along line
        float t = local_9c; // some t from collision output
        Vector3 interpolated;
        interpolated.x = from->x + (to->x - from->x) * t;
        interpolated.y = from->y + (to->y - from->y) * t;
        interpolated.z = from->z + (to->z - from->z) * t;
        float dx = from->x - interpolated.x;
        float dy = from->y - interpolated.y;
        float dz = from->z - interpolated.z;
        float distSq = dx*dx + dy*dy + dz*dz;
        if (distSq < gEpsilon) {
            return true;
        }
    } else {
        // Entity is valid
        if ((flags & 1) != 0) {
            Component* healthComp = getComponent(hitEntity, 0x63c15f4e); // "HealthComponent" hash
            if (healthComp != nullptr) {
                // Entity has health component → treat as alive, visible
                return true;
            }
        }
        if ((flags & 2) != 0) {
            Vehicle* vehicle = getVehicleOfEntity(hitEntity); // FUN_006bea40
            if (vehicle != nullptr) {
                // Check if vehicle is occupied/driven
                if (hasDriver(vehicle)) { // vtable call at offset +0x28
                    if (isAliveType(2)) { // FUN_009ae8a0
                        if (isPlayerEntity(*(Entity**)(this + 0x10))) { // FUN_009af6f0
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}
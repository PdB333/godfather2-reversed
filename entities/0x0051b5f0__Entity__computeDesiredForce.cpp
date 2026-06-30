// FUNC_NAME: Entity::computeDesiredForce
int __thiscall Entity::computeDesiredForce(Entity *this, Entity *other, float *output)
{
    float targetPos[4];
    float diff[4];
    float distance;
    float force;
    float dotProduct;
    float sqDist;
    float tmp;
    int collisionID;
    int result;
    float maxForce;
    float *pfVar1;
    float fVar8;

    // Get flags from some component (likely PhysicsComponent)
    uint flags = *(uint *)(*(int *)((char *)this + 0x10) + 0x14);
    // +0x10 points to a PhysicsComponent, +0x14 are flags

    if ((flags & 0x4000) == 0) {
        // Normal path: use this entity's own target position or compute from linked entity
        if (*(int *)((char *)this + 0xbc) == 0) { // +0xbc = targetEntityID? 0 means no target
            targetPos[0] = *(float *)((char *)this + 0x60); // +0x60-0x6c = current position
            targetPos[1] = *(float *)((char *)this + 0x64); // +100 decimal = 0x64
            targetPos[2] = *(float *)((char *)this + 0x68);
            targetPos[3] = *(float *)((char *)this + 0x6c);
        } else {
            // Compute target position from a linked entity (e.g. a bone)
            FUN_0056b420((char *)this + 0x30, *(int *)((char *)this + 0xbc), &targetPos);
        }
    } else {
        // Flag 0x4000 set: use predicted position = other's position + other's velocity
        targetPos[0] = *(float *)((char *)other + 0x70) + *(float *)((char *)other + 0x60);
        targetPos[1] = *(float *)((char *)other + 0x74) + *(float *)((char *)other + 0x64);
        targetPos[2] = *(float *)((char *)other + 0x78) + *(float *)((char *)other + 0x68);
        targetPos[3] = *(float *)((char *)other + 0x7c) + *(float *)((char *)other + 0x6c);
    }

    // Compute difference vector from other's position to target
    diff[0] = targetPos[0] - *(float *)((char *)other + 0x70);
    diff[1] = targetPos[1] - *(float *)((char *)other + 0x74);
    diff[2] = targetPos[2] - *(float *)((char *)other + 0x78);
    diff[3] = targetPos[3] - *(float *)((char *)other + 0x7c);

    // Compute distance
    sqDist = diff[0]*diff[0] + diff[1]*diff[1] + diff[2]*diff[2];
    distance = sqrtf(sqDist);

    // Dot product of other's velocity with difference vector
    dotProduct = *(float *)((char *)other + 0x60) * diff[0] +  // +0x60 = velocity X
                 *(float *)((char *)other + 0x64) * diff[1] +  // +0x64 = velocity Y
                 *(float *)((char *)other + 0x68) * diff[2];   // +0x68 = velocity Z

    // Default force = 1.0 (clamp max)
    force = DAT_00e2b1a4; // 1.0f? (max force constant)

    // Check if distance is within a threshold and not zero
    if (*(float *)((char *)other + 0x144) <= distance && distance != *(float *)((char *)other + 0x144)) {
        // Compute force based on distance and a scale factor
        double scale = (double)(*(float *)((char *)other + 0x14c) * DAT_00e2cd54); // +0x14c = some parameter
        FUN_00b9c041(); // probably some random variation or noise
        force = *(float *)((char *)this + 0x88) / 
                ((float)scale * distance * DAT_00e2b1a0 + (float)PTR_FUN_00e4462c); // constant fudge
        if (force >= 0.0f) {
            if (force <= DAT_00e2b1a4) goto LAB_0051b73b;
        } else {
            force = 0.0f;
        }
        // Clamp force to max if exceeding
        force = DAT_00e2b1a4;
    }
LAB_0051b73b:
    // Prepare output vectors (targetPos reused for output)
    targetPos[0] = targetPos[0]; // actually these are the target position but we overwrite force later
    targetPos[1] = targetPos[1];
    targetPos[2] = targetPos[2];
    targetPos[3] = *(float *)((char *)this + 0x88); // +0x88 = some height/force component?

    // Check additional flag for distance-based force reduction
    if ((flags & 0x200000) != 0) {
        fVar8 = *(float *)(*(int *)((char *)this + 0x10) + 0x24); // some threshold
        if (fVar8 <= distance) {
            force = 0.0f;
        } else {
            fVar8 = distance / fVar8;
            fVar8 = fVar8 * fVar8 * fVar8 * fVar8; // fVar8^4
            force = (DAT_00e2b1a4 - (DAT_00e445ac - fVar8 * DAT_00e2b04c) * fVar8 * fVar8) * force;
        }
    }

    // Check collision with some function; returns 0,1,2? - 0 or 1 means clear?
    collisionID = FUN_004bdae0(&targetPos); // likely a collision check at computed point
    if ((collisionID != 0 && collisionID != 1) ||
        (pfVar1 = (float *)(*(int *)((char *)this + 0x10) + 0x28), 
         force < *pfVar1 || force == *pfVar1)) {
        result = 0; // collision or force too small
    } else {
        result = 1; // valid
    }

    // Store output values if requested
    if (output != (float *)0x0) {
        output[1] = force;        // force magnitude
        *output = dotProduct;     // dot product (for steering?)
        output[2] = distance;     // distance
    }

    return result;
}
// FUNC_NAME: Entity::computeVerticalMovementStep
float __thiscall Entity::computeVerticalMovementStep(Entity *this, float *sourcePos, float *targetPos, float deltaTime)
{
    float yDiff = targetPos[1] - sourcePos[1]; // Y-axis difference
    // Check if the absolute Y difference is at least a minimum threshold (using integer bit hack for fabs)
    if (DAT_00e44598 <= *(float *)&((*(uint32_t *)&yDiff) & DAT_00e44680)) {
        float srcX = sourcePos[0];
        float tgtX = targetPos[0];
        float xDiff = srcX - tgtX;
        float srcZ = sourcePos[2];
        float tgtZ = targetPos[2];
        
        Entity *velocityProvider = nullptr;
        if (*(uint32_t *)((uint8_t *)this + 0x48) != 0) {
            velocityProvider = (Entity *)(*(uint32_t *)((uint8_t *)this + 0x48) - 0x48); // Adjust pointer to get base of velocity component
        }
        
        float velocityVec[3];
        // Call virtual function at vtable+0x4c to get velocity vector
        (*(void (__thiscall *)(Entity *, float *))(*(uint32_t **)velocityProvider)[0x13])(velocityProvider, velocityVec);
        
        float speed = sqrtf(velocityVec[0] * velocityVec[0] + velocityVec[1] * velocityVec[1] + velocityVec[2] * velocityVec[2]);
        if (speed <= DAT_00e44598) {
            speed = DAT_00d5eee4; // Use epsilon if too slow
        }
        
        float distance = sqrtf((srcZ - tgtZ) * (srcZ - tgtZ) + xDiff * xDiff + (srcX - tgtX) * (srcX - tgtX));
        float step = (speed * deltaTime) / distance;
        
        float yStep = step * yDiff;
        // Clamp yStep magnitude to not exceed the remaining yDiff
        if (_DAT_00d5780c < *(float *)&((*(uint32_t *)&yStep) & DAT_00e44680)) {
            return yDiff; // Return raw difference to prevent overshoot
        }
        return yStep;
    }
    return 0.0f;
}
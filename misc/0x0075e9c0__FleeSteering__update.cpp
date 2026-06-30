// FUNC_NAME: FleeSteering::update
void __thiscall FleeSteering::update(void* this, float deltaTime) {
    // Get target position (likely player position from global manager)
    void* playerData = getPlayerPositionData();
    float deltaX = *(float*)((int)this + 0x60) - *(float*)((int)playerData + 0x30);
    float deltaZ = *(float*)((int)this + 0x68) - *(float*)((int)playerData + 0x38);
    float deltaY = 0.0f; // Ground plane movement, ignore Y

    float distanceSq = vec3LengthSq(&deltaX, &deltaX); // &deltaX used twice for x, but vec3LengthSq expects 3 components? Actually it's a trick: it computes length squared of (dx,dy,dz) but addresses are same for all? In original decompiler it took two pointers, but likely it's a function that takes a vector pointer and returns length squared. We'll assume it computes sqrt(dx^2+dy^2+dz^2) but given dy=0, it's just dx^2+dz^2.

    if (distanceSq > steeringDistanceThreshold) {
        // Compute desired velocity away from target (flee behavior)
        void* owner = *(void**)((int)this + 0x58);
        float maxSpeed = (*(float(__thiscall**)(void*))(*(int*)owner + 0x1c0))(owner);
        float invFactor = maxSpeed * maxSpeed / (distanceSq * decelerationFactor);
        float velX = deltaX * invFactor;
        float velY = deltaY * invFactor; // deltaY=0
        float velZ = deltaZ * invFactor;
        *(float*)((int)this + 0x110) = velX;
        *(float*)((int)this + 0x114) = velY;
        *(float*)((int)this + 0x118) = velZ;

        // Calculate new velocity after applying deltaTime (prediction)
        float newVelX = velX * deltaTime + deltaX * maxSpeed;
        float newVelY = velY * deltaTime + deltaY * maxSpeed;
        float newVelZ = velZ * deltaTime + deltaZ * maxSpeed;

        // Check if we are moving away from target sufficiently (dot product)
        float dot = deltaX * newVelX + deltaY * newVelY + deltaZ * newVelZ;
        if (dot > arrivalDotThreshold) {
            // Apply the computed velocity to owner
            *(unsigned long long*)((int)owner + 0x424) = (unsigned long long)(*(unsigned int*)&newVelY) << 32 | *(unsigned int*)&newVelX;
            *(float*)((int)owner + 0x42c) = newVelZ;
        } else {
            // Cap velocity to direction away at maximum speed
            float scale = distanceSq / deltaTime; // Note: in original it's (float)fVar2 / param_2, where fVar2 is sqrt(distanceSq)? Actually fVar2 is the result of FUN_0056afa0 which likely returns the actual distance (sqrt). But the code uses fVar2 (float10) then casts to float. So distanceSq is squared distance, fVar2 is distance. We need to clarify. In decompiler, fVar2 is result of FUN_0056afa0(&local_20,&local_20). That function likely returns the length (sqrt of sum of squares). So we need to compute actual distance using sqrt(distanceSq). We'll assume vec3Length returns length.
            // We'll correct: float distance = sqrt(distanceSq);
            // scale = distance / deltaTime;
            float distance = sqrt(distanceSq);
            float arrivalScale = distance / deltaTime;
            float cappedVelX = deltaX * arrivalScale;
            float cappedVelY = deltaY * arrivalScale; // zero
            float cappedVelZ = deltaZ * arrivalScale;
            *(unsigned long long*)((int)owner + 0x424) = (unsigned long long)(*(unsigned int*)&cappedVelY) << 32 | *(unsigned int*)&cappedVelX;
            *(float*)((int)owner + 0x42c) = cappedVelZ;
        }
    } else {
        // Distance is less than threshold, set arrived flag
        *(unsigned char*)((int)this + 0x11c) = 1;
    }
}
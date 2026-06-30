// FUNC_NAME: ArriveBehavior::updateArrive
void __thiscall ArriveBehavior::updateArrive(ArriveBehavior* this, float deltaTime)
{
    // Constants from global memory (likely configured in game settings)
    // _DAT_00d577a0: some speed threshold for arrival condition (perhaps maxSpeed)
    // DAT_00d64cc0: minimum timer value to allow deceleration
    // _DAT_00d5780c: speed multiplier when arrival condition is met
    extern float gArriveSpeedThreshold;   // _DAT_00d577a0
    extern float gArriveMinTimer;         // DAT_00d64cc0
    extern float gArriveSpeedFactor;      // _DAT_00d5780c

    float targetX, targetY, targetZ;
    float *targetPtr;

    if (deltaTime <= 0.0f)
        return;

    // Get target object pointer (offset +0x54)
    targetPtr = *(float**)(this + 0x54);   // +0x54: pointer to target object (may be null)

    if (targetPtr == nullptr)
    {
        // No target: reset target position to origin
        targetX = 0.0f;
        targetY = 0.0f;
        targetZ = 0.0f;
    }
    else if ((*(uint8*)(this + 0x94) & 1) == 0)   // +0x94: flags byte, bit0 = use virtual getter?
    {
        // Use virtual method to get target position (likely writes 8 bytes: x,y)
        (*(void (__thiscall**)(void*))(*targetPtr + 0x4c))(&targetX);
        // Note: targetZ remains unchanged from initialization (0.0f) – maybe ignored in this path
        // Possibly targetZ is overwritten later by ground height.
    }
    else
    {
        // Direct fetch from target object fields (offsets +0x109, +0x10b * 4)
        targetX = *(float*)(targetPtr + 0x109);   // +0x424
        targetY = *(float*)(targetPtr + 0x10a);   // +0x428
        targetZ = *(float*)(targetPtr + 0x10b);   // +0x42C
    }

    // Get ground height (or global reference position) from global function
    int globalPtr = FUN_00471610();   // Returns pointer to global data (e.g., Transform)
    float groundZ = *(float*)(globalPtr + 0x38);    // +0x38: Z component of global target

    // Current position of this object (offsets +0x68, +0x6c, +0x70)
    float curX = *(float*)(this + 0x68);
    float curY = *(float*)(this + 0x6c);
    float curZ = *(float*)(this + 0x70);

    // Compute difference vector: (curPos - targetPos) where target Z = groundZ
    float deltaX = curX - targetX;
    float deltaY = curY - targetY;
    float deltaZ = curZ - groundZ;

    float currentSpeed = *(float*)(this + 0x64);    // +0x64: current speed limit or radius
    float distanceSq = deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ;
    float distance = sqrt(distanceSq);

    // Arrival condition: either speed limit is very small, or distance is within arrival radius scaled by time, or timer expired
    if ( (currentSpeed <= gArriveSpeedThreshold) ||
         (distance <= currentSpeed * deltaTime) ||
         (*(float*)(this + 0x60) < gArriveMinTimer) )   // +0x60: deceleration timer
    {
        // Arrived: set velocity to target direction scaled by factor/deltaTime
        float invDelta = gArriveSpeedFactor / deltaTime;
        targetX = deltaX * invDelta;   // reuse targetX,Y,Z as velocity
        targetY = deltaY * invDelta;
        targetZ = deltaZ * invDelta;
        *(uint8*)(this + 0x80) = 1;   // +0x80: arrival flag (byte)
    }
    else
    {
        // Not yet arrived: normalize direction and scale by speed, then decelerate
        // FUN_0043a210 likely normalizes the vector and stores result back into local_34 (targetX,targetY) and local_1c (targetZ? Actually local_1c is deltaX? wait)
        // But here we reinterpret: call to normalize (dx,dy,dz) and produce unit direction.
        FUN_0043a210(&targetX, &deltaX);   // assumes targetX, targetY, targetZ are input/output? Hard to match exactly.

        // After normalization, targetX,targetY,targetZ become unit vector components multiplied by speed limit
        float speedLimit = currentSpeed;
        targetX *= speedLimit;
        targetY *= speedLimit;
        targetZ *= speedLimit;

        // Decrement timer (offset +0x60)
        *(float*)(this + 0x60) -= deltaTime;
    }

    // Apply the computed velocity (or direct position update)
    // FUN_00754c90 likely updates position using velocity from targetX,targetY,targetZ
    FUN_00754c90(&targetX);

    // Call a virtual event/method if a handler object exists (offset +0x48)
    int* handler = *(int**)(this + 0x48);
    if (handler != nullptr)
    {
        // Dereference handler's vtable (offset -0x48 from its base?) and call method at +0x168
        // This pattern suggests handler is a derived class with a base class offset.
        (*(void (__thiscall**)(void))(*((int*)handler - 0x48) + 0x168))();
    }
    else
    {
        // Default global callback at iRam00000000 + 0x168 (likely a global function pointer)
        (*(void (__thiscall**)(void))(iRam00000000 + 0x168))();
    }
}
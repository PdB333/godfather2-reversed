// FUNC_NAME: WheeledVehicle::updateSuspension

void __fastcall WheeledVehicle::updateSuspension(WheeledVehicle* this)
{
    // Offsets:
    // +0x2b4: m_speed (float)
    // +0x2d0: m_pPhysicsBody (pointer to HavokVehicle or similar)
    // +0x11c: m_minSuspensionCompression (float)
    // +0x13c: m_maxSuspensionCompression (float)
    // +0x210: m_airborneOverride (float)
    // +0xe8: m_springConstant (float)
    // +0x60: m_maxSpringDelta (float)
    // +0x240: m_targetSpringValue (float)
    // +0x284: m_currentSpringValue (float)
    // +0xf0: m_dampingFactor (float)
    // +0x23c: m_springForce (float)
    // +0x244: m_damperForce (float)

    float speed = *(float*)(this + 0x2b4);
    void* physicsBody = *(void**)(this + 0x2d0);
    bool isOnGround = (*(byte*)((int)physicsBody + 0x8e3) & 1) == 0;

    // Get frame timing info
    int timeMgr = FUN_00471610(); // returns pointer to time manager
    float frameTime = *(float*)(timeMgr + 0x34); // high part of 64-bit value at +0x30
    float time = *(float*)(timeMgr + 0x30);      // low part
    float someTime = *(float*)(timeMgr + 0x38);  // another time value

    float suspensionInput;
    if (isOnGround)
    {
        // Interpolate suspension compression based on speed
        float minComp = *(float*)(this + 0x11c);
        float maxComp = *(float*)(this + 0x13c);
        suspensionInput = (maxComp - minComp) * speed + minComp;
    }
    else
    {
        // Use override value when airborne
        suspensionInput = *(float*)(this + 0x210);
    }

    float springConstant = *(float*)(this + 0xe8);
    if (!isOnGround)
    {
        springConstant = _DAT_00d5780c; // likely 1.0f
    }

    float maxDelta = *(float*)(this + 0x60);
    float target = *(float*)(this + 0x240);
    float ratio = 0.0f;
    if (DAT_00e44598 < maxDelta) // epsilon check
    {
        ratio = ((suspensionInput + frameTime) - target) / maxDelta;
    }

    // Smoothly update current spring value
    float current = *(float*)(this + 0x284);
    float newCurrent = smoothInterp(current, ratio, springConstant);
    *(float*)(this + 0x284) = newCurrent;

    // Apply damping
    float damping = *(float*)(this + 0xf0);
    float dampFactor = 0.0f;
    if (damping > 0.0f && damping < _DAT_00d5780c)
    {
        dampFactor = damping;
    }
    *(float*)(this + 0x284) = newCurrent - newCurrent * dampFactor;

    // Update spring force with lerp towards time
    float springForce = *(float*)(this + 0x23c);
    float newSpringForce = smoothInterp(springForce, time, 1.0f);
    *(float*)(this + 0x23c) = newSpringForce;

    // Update damper force with lerp towards someTime
    float damperForce = *(float*)(this + 0x244);
    float newDamperForce = smoothInterp(damperForce, someTime, 1.0f);
    *(float*)(this + 0x244) = newDamperForce;

    // Update target spring value for next frame
    *(float*)(this + 0x240) = *(float*)(this + 0x284) * maxDelta + target;
}
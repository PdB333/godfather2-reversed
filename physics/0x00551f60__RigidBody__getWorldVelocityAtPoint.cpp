// FUNC_NAME: RigidBody::getWorldVelocityAtPoint
void __thiscall RigidBody::getWorldVelocityAtPoint(RigidBody* this, const float* worldPoint, float* outVelocity)
{
    // +0x60: positionX (center of mass)
    // +0x64: positionY
    // +0x68: positionZ
    float posX = *(float*)((uintptr_t)this + 0x60);
    float posY = *(float*)((uintptr_t)this + 0x64);
    float posZ = *(float*)((uintptr_t)this + 0x68);

    // Delta from center of mass to world point
    float dx = worldPoint[0] - posX;
    float dy = worldPoint[1] - posY;
    float dz = worldPoint[2] - posZ;

    // +0xe0: angularVelocityX
    // +0xe4: angularVelocityY
    // +0xe8: angularVelocityZ
    float omegaX = *(float*)((uintptr_t)this + 0xe0);
    float omegaY = *(float*)((uintptr_t)this + 0xe4);
    float omegaZ = *(float*)((uintptr_t)this + 0xe8);

    // Compute cross product: omega x delta
    // velocity_at_point = linearVelocity + angularVelocity x (point - centerOfMass)
    float crossX = omegaY * dz - omegaZ * dy;
    float crossY = omegaZ * dx - omegaX * dz;
    float crossZ = omegaX * dy - omegaY * dx;

    // +0xd0: linearVelocityX
    // +0xd4: linearVelocityY
    // +0xd8: linearVelocityZ
    // +0xdc: padding/unknown (often zero or extra data)
    outVelocity[0] = *(float*)((uintptr_t)this + 0xd0) + crossX;
    outVelocity[1] = *(float*)((uintptr_t)this + 0xd4) + crossY;
    outVelocity[2] = *(float*)((uintptr_t)this + 0xd8) + crossZ;
    outVelocity[3] = *(float*)((uintptr_t)this + 0xdc); // may be zero or unused
}
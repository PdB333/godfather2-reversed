// FUNC_NAME: Entity::getSpeed
// Function address: 0x006c93c0
// Returns the magnitude of the entity's velocity vector, clamped to zero below a global threshold.

float Entity::getSpeed() const
{
    float speed = 0.0f;
    if (this != nullptr)
    {
        // Call virtual function at vtable+0x4c to get velocity (Vec3)
        // Output is 3 floats: local_1c (x), fStack_18 (y), fStack_14 (z)
        Vec3 velocity;
        (this->vtable->getVelocity)(&velocity);

        // Compute magnitude: sqrt(x^2 + y^2 + z^2)
        speed = sqrtf(velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z);

        // Apply dead zone: if speed is less than global threshold (DAT_00d5ef84), treat as zero
        if (speed < gSpeedThreshold) // DAT_00d5ef84
        {
            speed = 0.0f;
        }
    }

    return speed;
}
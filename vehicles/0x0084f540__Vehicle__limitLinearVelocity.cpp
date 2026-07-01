// FUNC_NAME: Vehicle::limitLinearVelocity

#include <cmath>

// External function, possibly related to floating-point consistency or math initialization.
extern void FUN_009f2000();

// Global constant (acceleration factor? drag? unknown)
extern const float g_accelerationFactor = 0.0f; // Placeholder for DAT_012067e8

void Vehicle::limitLinearVelocity(float dt, float maxSpeed)
{
    // Offsets from this pointer (struct members)
    // +0x1A0: linearVelocity.x
    // +0x1A4: linearVelocity.y
    // +0x1A8: linearVelocity.z
    // +0x1AC: speedScalar (set during this function)
    // +0x0D0: pointer to physics component (with vtable at +0x00, virtual function at +0x40)

    float velX = *(float*)(this + 0x1A0);
    float velY = *(float*)(this + 0x1A4);
    float velZ = *(float*)(this + 0x1A8);

    float magnitude = sqrtf(velX * velX + velY * velY + velZ * velZ);
    float clampedMag = g_accelerationFactor * dt + magnitude;

    if (maxSpeed < clampedMag) {
        clampedMag = maxSpeed;
    }

    float scale = clampedMag / magnitude;

    velX *= scale;
    velY *= scale;
    velZ *= scale;

    // Update speed scalar at +0x1AC
    *(float*)(this + 0x1AC) *= scale;

    // Call external helper function
    FUN_009f2000();

    // Call virtual function on physics component: setLinearVelocity
    void* physicsComponent = *(void**)(this + 0xD0);
    void** vtable = *(void***)physicsComponent;
    void* func = vtable[0x40 / sizeof(void*)];
    ((void (*)(void*, float*))func)(physicsComponent, &velX);
}
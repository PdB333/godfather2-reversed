// FUNC_NAME: Entity::updateAttractionToTarget
// Address: 0x007447a0
// Role: Computes a direction vector from this object's position (offsets +0xF4, +0xF8, +0xFC) to a global target point
//       (DAT_00e44564), scales it by a global speed factor (DAT_00e518e0) * deltaTime, and applies it via FUN_00470040.
//       Typically used to pull an entity toward a fixed coordinate (e.g. origin or a debug attractor).

void __thiscall Entity::updateAttractionToTarget(void* this, float deltaTime)
{
    float dx; // difference in x
    float dy; // difference in y
    float dz; // difference in z
    float scaledSpeed; // speed factor * deltaTime

    // Global target coordinates (all components equal – likely zero or a constant point)
    float targetX = DAT_00e44564;
    float targetY = DAT_00e44564;
    float targetZ = DAT_00e44564;

    // Read position from object struct (offsets relative to this)
    // +0xF4: x position (float)
    // +0xF8: y position (float)
    // +0xFC: z position (float)
    float objX = *(float*)((int)this + 0xF4);
    float objY = *(float*)((int)this + 0xF8);
    float objZ = *(float*)((int)this + 0xFC);

    // Direction from object toward target
    dx = targetX - objX;
    dy = targetY - objY;
    dz = targetZ - objZ;

    // Scale by global speed multiplier and frame time
    scaledSpeed = DAT_00e518e0 * deltaTime;

    // Apply the resulting vector – FUN_00470040 expects a Vec3* (dx, dy, dz) and the scaled speed
    // Parameter 0 likely controls mode (e.g. force vs velocity)
    FUN_00470040(&dx, scaledSpeed, 0);
}
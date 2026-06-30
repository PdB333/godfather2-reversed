// FUNC_NAME: Entity::getVelocityMagnitude

// Address: 0x006c93c0
// Role: Computes the magnitude of the velocity vector, returning zero if below epsilon threshold.
// The virtual function at vtable+0x4c (index 0x13) is assumed to retrieve the velocity as a Vec3.

// Global epsilon for ignoring small speeds (defined elsewhere)
extern float g_fVelocityEpsilon; // Default 0.0f or small value; DAT_00d5ef84

class Entity {
public:
    // Virtual function at vtable+0x4c: writes velocity to a Vec3 (3 floats: x, y, z)
    // This is a placeholder; the actual class hierarchy may vary.
    virtual void getVelocity(Vec3& outVec) = 0;

    float getVelocityMagnitude() const {
        float magnitude = 0.0f;
        if (this != nullptr) {
            Vec3 vel; // local_1c (x), fStack_18 (y), fStack_14 (z)
            // Call virtual function at offset 0x4c (index = 0x4c / 4 = 19)
            (**(void (__thiscall**)(const Entity*, Vec3*))(*(uint32*)this + 0x4c))(this, &vel);
            magnitude = sqrt(vel.x * vel.x + vel.y * vel.y + vel.z * vel.z);
            if (magnitude < g_fVelocityEpsilon) {
                magnitude = 0.0f;
            }
        }
        return magnitude;
    }
};
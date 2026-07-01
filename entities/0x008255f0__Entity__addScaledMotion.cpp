// FUNC_NAME: Entity::addScaledMotion
// Function at 0x008255f0: Adds a scaled motion state from another entity to this entity's motion state.
// The motion state consists of three Vector4 components (likely linear velocity, angular velocity, and force/acceleration).
// Offsets: +0x50: first vector, +0x60: second, +0x70: third.
// This is used for interpolation or blending of physics states.

struct MotionState {
    float linear[4];   // +0x50
    float angular[4];  // +0x60
    float other[4];    // +0x70
};

class Entity {
public:
    MotionState motionState; // at offset 0x50 (may be part of larger structure)

    // Adds source->motionState scaled by scale to this->motionState.
    void __thiscall addScaledMotion(const Entity* source, float scale);
};

void __thiscall Entity::addScaledMotion(const Entity* source, float scale) {
    MotionState& dest = this->motionState;
    const MotionState& src = source->motionState;

    // Add each component of the first vector (linear velocity)
    dest.linear[0] += src.linear[0] * scale;
    dest.linear[1] += src.linear[1] * scale;
    dest.linear[2] += src.linear[2] * scale;
    dest.linear[3] += src.linear[3] * scale;

    // Add each component of the second vector (angular velocity)
    dest.angular[0] += src.angular[0] * scale;
    dest.angular[1] += src.angular[1] * scale;
    dest.angular[2] += src.angular[2] * scale;
    dest.angular[3] += src.angular[3] * scale;

    // Add each component of the third vector (force/other)
    dest.other[0] += src.other[0] * scale;
    dest.other[1] += src.other[1] * scale;
    dest.other[2] += src.other[2] * scale;
    dest.other[3] += src.other[3] * scale;
}
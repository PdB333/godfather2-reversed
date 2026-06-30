// FUNC_NAME: AIEntity::isTargetInCone
// Function address: 0x006E5BB0
// Checks if a target position is within the AI's field of view (cone) based on its current state.
// The AI has a forward direction vector and orientation quaternion.
// State 0x04 = alert/aggressive? 0x02 = idle/patrol?
// Returns 0 if target is visible, 1 if not.

float g_visionConeThreshold = *(float*)0x00d577a0; // Global threshold for state 0x02

class AIEntity
{
public:
    // +0x04: unknown (likely vtable pointer)
    // +0x08...0x19: other fields
    // +0x1C: unknown
    // +0x20: forwardDirection (float3) – unit vector indicating which way the entity is facing
    // +0x2C: orientationQuat ( __m128? actually 8 bytes? Might be a quaternion stored as two floats? 
    // We'll assume it's a quaternion (x,y,z,w) but the decompiler sees 8 bytes at +0x2C, 
    // so perhaps it's a packed quaternion with half floats? We'll treat as a custom struct.)
    // +0x34: unknown (float? set but unused in this func)
    // +0x38...0x43: more fields
    // +0x44: position.x (float)
    // +0x48: position.y (float)
    // +0x4C: position.z (float)
    // +0x88: state (char) – 0x04 = alert, 0x02 = idle, others = irrelevant

    char state; // offset 0x88
    float position[3]; // offset 0x44
    // orientation likely at 0x2C
    // forwardDirection at 0x20

    // Helper function: transforms a vector by the orientation quaternion.
    // Destination = vector in local space (relative to entity's orientation)
    void transformByOrientation(const float* input, float* output);

    // Method: checks if a target point is within the visible cone
    int __thiscall isTargetInCone(const float* targetPos)
    {
        char state = *(char*)(this + 0x88); // +0x88
        if (state != 4 && state != 2)
            return 1; // Not visible in non-alert/idle states

        // Vector from entity to target
        float diff[3];
        diff[0] = targetPos[0] - *(float*)(this + 0x44); // position.x
        diff[1] = targetPos[1] - *(float*)(this + 0x48); // position.y
        diff[2] = targetPos[2] - *(float*)(this + 0x4C); // position.z

        // Transform diff into local space using orientation quaternion at +0x2C
        // The quaternion is 8 bytes (likely two floats? But the decompiler treats it as undefined8)
        // We'll assume a function that takes a 3-vector and orientation and outputs local vector.
        float localDiff[3];
        // FUN_004a07f0 does the transform; we'll simulate it
        // We'll call a helper function that uses the quaternion at +0x2C
        this->transformByOrientation(diff, localDiff);

        // Compute dot product of forward direction (at +0x20) with localDiff
        float forward[3];
        forward[0] = *(float*)(this + 0x20);
        forward[1] = *(float*)(this + 0x24);
        forward[2] = *(float*)(this + 0x28);
        float dot = forward[0] * localDiff[0] + forward[1] * localDiff[1] + forward[2] * localDiff[2];

        if (state == 4)
        {
            // Alert state: target must be in front (dot > 0)
            if (dot <= 0.0f)
                return 1;
        }
        else if (state == 2)
        {
            // Idle state: target must be within a wider cone defined by global threshold
            if (g_visionConeThreshold <= dot)
                return 1;
        }
        return 0; // Target is visible
    }
};
// FUNC_NAME: Entity::setTransformData
// Address: 0x004c5da0
// Role: Sets 4 qwords of transform data from source pointer; if this entity is the active global entity, updates two auxiliary transform vectors.

// Forward declarations
class Entity; // Assume class exists with fields at offsets as below
void updateTransformVector(int entityIndex, int vectorIndex, const Vector3& vec); // Placeholder for FUN_0060add0

// Static global active entity pointer (likely singleton)
extern Entity* g_activeEntity;

// Assumed structure for a 3D vector with w=0 (padded to 16 bytes)
struct Vector3 {
    float x, y, z; // +0x00, +0x04, +0x08
    float w;       // +0x0C (unused here)
};

void Entity::setTransformData(const uint64_t* sourceData) {
    // Copy 4 qwords from source into object fields at offsets 0xBC, 0xC4, 0xCC, 0xD4
    // These likely represent two quaternions or two sets of 4 floats (e.g., position + orientation)
    *(uint64_t*)((uint8_t*)this + 0xBC) = sourceData[0];  // +0xBC: first qword
    *(uint64_t*)((uint8_t*)this + 0xC4) = sourceData[1];  // +0xC4: second qword
    *(uint64_t*)((uint8_t*)this + 0xCC) = sourceData[2];  // +0xCC: third qword
    *(uint64_t*)((uint8_t*)this + 0xD4) = sourceData[3];  // +0xD4: fourth qword

    // If this entity is the active global one, update two auxiliary vectors
    if (g_activeEntity == this) {
        // Build first vector from first two qwords: (low of q0, low of q1, high of q0)
        Vector3 vec1;
        vec1.x = *(float*)((uint8_t*)this + 0xBC);  // low dword of q0
        vec1.y = *(float*)((uint8_t*)this + 0xC4);  // low dword of q1
        vec1.z = *(float*)((uint8_t*)this + 0xC0);  // high dword of q0
        vec1.w = 0.0f;                               // maintain padded zero
        // Call with arg1: field at +0x10 (likely an index/ID), arg2: field at +0xA4 (another index)
        updateTransformVector(*(int*)((uint8_t*)this + 0x10), *(int*)((uint8_t*)this + 0xA4), vec1);

        // Build second vector from third and fourth qwords: (high of q2, low of q3, high of q3)
        Vector3 vec2;
        vec2.x = *(float*)((uint8_t*)this + 0xD0);  // high dword of q2
        vec2.y = *(float*)((uint8_t*)this + 0xD4);  // low dword of q3
        vec2.z = *(float*)((uint8_t*)this + 0xD8);  // high dword of q3
        vec2.w = 0.0f;
        // Call with arg1: same +0x10, arg2: field at +0xA8
        updateTransformVector(*(int*)((uint8_t*)this + 0x10), *(int*)((uint8_t*)this + 0xA8), vec2);
    }
}
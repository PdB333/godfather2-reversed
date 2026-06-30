// FUNC_NAME: EntitySystem::validateTargetDistance
// Address: 0x00745340
// Role: Checks if a target entity (referenced by handle) is within a given squared distance from another entity.
//       Returns a handle that includes a type tag (low byte = 1) if distance is within range, otherwise clears the tag.
//       The handle is derived from the target entity's position field address.

#include <cstdint>

// Forward declaration of external function (returns some entity pointer)
void* FUN_00471610();

// Structure for a 3D position (at offset 0x30)
struct Vector3 {
    float x; // +0x00
    float y; // +0x04
    float z; // +0x08
};

// Assumed entity structure with position at offset 0x30
struct Entity {
    // ... padding ...
    Vector3 position; // +0x30
    // ... rest ...
};

// Class that owns this method (inferred from use of offset 0x5C)
class EntitySystem {
public:
    uint32_t __thiscall validateTargetDistance(float maxDistanceSq);
private:
    // unknown members, at offset 0x5C a handle/ID
};

uint32_t __thiscall EntitySystem::validateTargetDistance(float maxDistanceSq) {
    uint32_t targetHandle = *(uint32_t*)((uint8_t*)this + 0x5C);
    if (targetHandle != 0 && targetHandle != 0x48) {
        // Get two entity pointers (likely self and target, or two endpoints)
        Entity* entityA = (Entity*)FUN_00471610();
        Entity* entityB = (Entity*)FUN_00471610();

        // Compute squared distance between their positions
        float dx = entityA->position.x - entityB->position.x;
        float dy = entityA->position.y - entityB->position.y;
        float dz = entityA->position.z - entityB->position.z;
        float distSq = dx*dx + dy*dy + dz*dz;

        // Build a handle from entityB's position address (as per decompiler)
        // This is likely a packed handle: high 24 bits = (address of position field) >> 8, low byte = 1 (type tag)
        uint32_t addrPart = ((uint32_t)(&entityB->position) >> 8) & 0xFFFFFF00;
        uint32_t newHandle = addrPart | 0x1;

        if (distSq <= maxDistanceSq) {
            return newHandle;
        } else {
            // Clear the type tag to indicate invalid
            return newHandle & 0xFFFFFF00;
        }
    }
    // Return original handle with low byte cleared
    return targetHandle & 0xFFFFFF00;
}
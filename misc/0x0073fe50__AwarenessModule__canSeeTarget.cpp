// FUNC_NAME: AwarenessModule::canSeeTarget
// Address: 0x0073fe50
// Role: Checks if the stored target entity is visible/within detection range of the player, based on distance, line-of-sight, and flag checks.
// This function likely belongs to a perception/awareness component in the EARS engine.

#include <cstdint>

// Forward declarations for external functions
bool isValidTarget(uint32_t targetHandle); // FUN_00726f50 - checks if target handle is valid/alive
uint32_t getPlayerTransform(); // FUN_00471610 - returns pointer to player's transform (pos + forward)
void normalizeVector3(float* out, float* in, int dummy); // FUN_0054ba20 and FUN_0043a210 - normalize 3D vector
void getEntityForwardVector(float* out); // FUN_007266b0 - writes entity forward vector to out

// Global constants (from data section)
extern float g_sightRange;          // DAT_00e51af0 - maximum detection distance
extern float g_dotProductThreshold; // _DAT_00d5efe0 - minimum dot product for field-of-view

// Bit masks for entity flags at offset 0xC8 (200 decimal)
enum EntityFlags : uint32_t {
    kFlagVisible = 0x01,       // bit 0: entity is currently visible
    kFlagInRange = 0x02,       // bit 1: entity is within range
    kFlagBehindCover = 0x10    // bit 4: entity is behind cover (partially hidden)
};

// Structure representing a 3D vector
struct Vector3 {
    float x, y, z;
};

// Structure returned by getPlayerTransform (assumed layout)
struct PlayerTransform {
    Vector3 forward;  // +0x20
    Vector3 position; // +0x30
    // other fields...
};

class AwarenessModule {
public:
    // Returns true if the target (stored at this+0x70) is within visibility/awareness of the player
    bool canSeeTarget() const;

private:
    // Offsets from this pointer (reconstructed from decompilation)
    // +0x5C: some handle/identifier for the target (used with isValidTarget)
    uint32_t m_targetHandle; 
    // +0x70: pointer to entity (or handle) that we are checking
    uint32_t m_targetEntity; 
    // +0xC8: flags for the target entity (bits described above)
    uint32_t m_entityFlags; 
};

bool AwarenessModule::canSeeTarget() const {
    uint32_t entity = *reinterpret_cast<uint32_t*>(reinterpret_cast<const uint8_t*>(this) + 0x70);

    // Early exit if entity is null or equals 0x48 (likely a dead/removed marker)
    if (entity == 0 || entity == 0x48) {
        return false;
    }

    uint32_t targetHandle = *reinterpret_cast<uint32_t*>(reinterpret_cast<const uint8_t*>(this) + 0x5C);
    uint32_t* playerTransformPtr = reinterpret_cast<uint32_t*>(getPlayerTransform()); // returns pointer to player's transform

    // Examine flags of the target entity (at offset 0xC8 from entity pointer)
    uint32_t entityFlags = *reinterpret_cast<uint32_t*>(entity + 0xC8);

    if ((entityFlags >> 1) & 1) { // bit 1 (kFlagInRange) is set
        // Entity is in range; check distance to player
        PlayerTransform* playerTransform = reinterpret_cast<PlayerTransform*>(playerTransformPtr);
        Vector3 delta;
        delta.x = playerTransform->position.x - *reinterpret_cast<float*>(entity + 0xE8);
        delta.y = playerTransform->position.y - *reinterpret_cast<float*>(entity + 0xEC);
        delta.z = playerTransform->position.z - *reinterpret_cast<float*>(entity + 0xF0);

        float distSq = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
        if (distSq > g_sightRange * g_sightRange) {
            return false; // too far
        }
        // fall through to further checks
    } else {
        // bit 1 not set; entity not in range
        if ((entityFlags & 0x11) == 0) { // both bit 0 and bit 4 are clear -> not visible and not behind cover
            return false;
        }
        // At least one of visible/behind cover is set; validate target handle
        if (!isValidTarget(targetHandle)) {
            return false;
        }
    }

    // Now check field-of-view (FOV) based on entity's state
    Vector3 vectorToTarget;
    Vector3 forwardPlayer;
    float dotProduct;

    if ((entityFlags & 0x12) == 0) { // bits 1 (inRange?) and 4 (behindCover) not set
        if ((entityFlags & kFlagVisible) == 0) {
            return true; // visible without line-of-sight check? (bit0 set)
        }
        // Compute direction from player to entity
        PlayerTransform* playerTransform = reinterpret_cast<PlayerTransform*>(playerTransformPtr);
        vectorToTarget.x = *reinterpret_cast<float*>(entity + 0xE8) - playerTransform->position.x;
        vectorToTarget.y = *reinterpret_cast<float*>(entity + 0xEC) - playerTransform->position.y;
        vectorToTarget.z = *reinterpret_cast<float*>(entity + 0xF0) - playerTransform->position.z;
        normalizeVector3(&vectorToTarget.x, &vectorToTarget.x, 0); // normalize direction

        // Get player's forward vector
        forwardPlayer = playerTransform->forward;
        normalizeVector3(&forwardPlayer.x, &forwardPlayer.x, 0);

        dotProduct = forwardPlayer.x * vectorToTarget.x + forwardPlayer.y * vectorToTarget.y + forwardPlayer.z * vectorToTarget.z;
    } else { // bits 1 or 4 set
        // Get entity's forward vector (from some internal storage)
        getEntityForwardVector(&vectorToTarget.x); // stores forward in vectorToTarget
        // Re-fetch player transform (may have changed)
        playerTransformPtr = reinterpret_cast<uint32_t*>(getPlayerTransform());
        PlayerTransform* playerTransform = reinterpret_cast<PlayerTransform*>(playerTransformPtr);
        forwardPlayer = playerTransform->forward;
        normalizeVector3(&forwardPlayer.x, &forwardPlayer.x, 0);
        // Normalize entity's forward
        normalizeVector3(&vectorToTarget.x, &vectorToTarget.x, 0);

        dotProduct = forwardPlayer.x * vectorToTarget.x + forwardPlayer.y * vectorToTarget.y + forwardPlayer.z * vectorToTarget.z;
    }

    // Compare dot product (cosine of angle) against threshold
    if (dotProduct >= g_dotProductThreshold) {
        return true;
    }
    return false;
}
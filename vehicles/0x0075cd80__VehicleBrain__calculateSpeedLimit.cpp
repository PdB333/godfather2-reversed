// FUNC_NAME: VehicleBrain::calculateSpeedLimit
// Address: 0x0075cd80
// Computes a speed limit for a vehicle, optionally reducing speed if a target entity is too close to the player's vehicle.

#include <cmath>

// Forward-declare the entity type with known offsets
struct Entity {
    float posX;            // +0x10
    float posZ;            // +0x14 (Z coordinate, Y in 3D terms)
    float boundingRadius;  // +0x18
};

// Tuning constants (replace with actual names from the binary if known)
extern float DAT_00e445f0;   // Base speed scale factor
extern float _DAT_00d5780c;  // Upper clamp for initial scaled speed
extern float DAT_00d636b8;   // Upper speed limit (or a force level)
extern float DAT_00d5eeec;   // Lower speed limit
extern float DAT_00e51978;   // Proximity threshold for speed reduction
extern float DAT_00e51974;   // Speed reduction factor when too close to player

// External helper functions
Entity* __cdecl FUN_00471610();  // Returns pointer to player's vehicle entity
float  __cdecl FUN_007fd800();   // Returns some time-based offset (e.g., prediction factor)

class VehicleBrain {
public:
    // Virtual function at vtable offset 0x1C0 – returns a base speed value
    virtual float getBaseSpeed() = 0;

    // noinline method: clamps/adapts speed according to distance to player vehicle
    float calculateSpeedLimit(int /*unused*/, Entity* targetEntity);
};

float VehicleBrain::calculateSpeedLimit(int, Entity* targetEntity) {
    float baseSpeed = getBaseSpeed();                       // virtual call
    float scaledSpeed = baseSpeed * DAT_00e445f0;

    float result = 0.0f;
    // Clamp scaledSpeed between 0 and _DAT_00d5780c
    if (scaledSpeed > 0.0f && scaledSpeed < _DAT_00d5780c) {
        result = scaledSpeed;
    }

    result *= DAT_00d636b8;

    if (targetEntity == nullptr) {
        // Player vehicle path – apply speed limits directly
        if (result <= DAT_00d5eeec) {
            return DAT_00d5eeec;               // enforce lower bound
        }
        if (result < DAT_00d636b8) {
            return DAT_00d636b8;               // enforce upper bound (or raised default)
        }
    } else {
        // Non-player vehicle: compare distance to player's vehicle
        Entity* playerVehicle = FUN_00471610();
        if (playerVehicle != nullptr) {
            float dx = targetEntity->posX - playerVehicle->posX;
            float dz = targetEntity->posZ - playerVehicle->posZ;
            float distance = std::sqrt(dx * dx + dz * dz);
            float closeness = distance - targetEntity->boundingRadius;
            float timeOffset = FUN_007fd800();

            // If the entity is far enough away (relative to threshold), reduce speed
            if ((closeness - timeOffset) > DAT_00e51978) {
                result *= DAT_00e51974;       // apply slowdown factor
                // Re-apply clamps after reduction
                if (result <= DAT_00d5eeec) {
                    return DAT_00d5eeec;
                }
                if (result < DAT_00d636b8) {
                    return DAT_00d636b8;
                }
            }
        }
    }

    return result;  // default: return the computed (or clamped) value
}
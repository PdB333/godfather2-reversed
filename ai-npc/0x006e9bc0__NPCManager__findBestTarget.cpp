// FUNC_NAME: NPCManager::findBestTarget
// Function address: 0x006e9bc0
// Searches through a list of entities (NPCs) to find the best match given a source position,
// type filter, distance range, directional cone, and optional predicate. Can also remove/disable
// a matched entity if the bRemove flag is set and the type matches.

#include <cstdlib>  // for rand()
#include <cmath>    // for sqrt? Not used directly.

// Forward declarations
class Entity;
class EntityManager; // Contains the list

// Constants (from data references)
static const float BEST_INITIAL_DISTANCE = *(float*)0x00d5f6f0;   // Initial best distance (large)
static const float RAND_MAX_INVERSE = *(float*)0x00e44590;        // 1.0 / RAND_MAX
static const float CONE_DOT_THRESHOLD = *(float*)0x00d5fb04;      // Dot product threshold for cone check
static const float GETTER_MAX_DIST_SQ = *(float*)0x00d5ddec;      // Max squared distance from getter position

// External helper functions (callees)
Entity* GetPlayerEntity();                          // FUN_00471610 - returns a global player/camera entity
void NormalizeVector(Vector3* vec);                 // FUN_0056afa0 - normalizes the vector
void ReleaseReference(int* refCount);               // FUN_004daf90 - decrements ref count and possibly frees
void NormalizeVector3(Vector3* vec);                // FUN_0043a210 - same as above? Different name.

// Entity structure (partial, based on offsets used)
struct Entity {
    // +0x6c position
    float posX; // +0x6c
    float posY; // +0x70
    float posZ; // +0x74
    // +0x98 type/ID? (int)
    int entityType; // +0x98
    // +0xa0 probability factor (float)
    float probabilityFactor; // +0xa0
    // +0xa4 max distance from getter (squared)
    float maxGetterDistSq; // +0xa4
    // +0xa8 active count (char)
    char activeCount; // +0xa8
    // ... other fields
};

// EntityManager (the 'this' object)
struct EntityManager {
    // +0x18 array of pointers to Entity
    Entity** entityArray; // +0x18
    // +0x1c count of entities
    int entityCount; // +0x1c
    // ... other fields
};

// Predicate callback type (for param_6)
typedef bool (*EntityPredicate)(Entity* entity); // Returns false to skip

// Main function
int __thiscall NPCManager::findBestTarget(
    EntityManager* thisPtr,       // param_1
    int targetType,               // param_2 - entity type to search (0x48? or 0 for all)
    char bRemove,                 // param_3 - if true and type matches, decrement active count and release ref
    Vector3* sourcePosition,      // param_4 - position to measure distance from
    float minDistSq,              // param_5 - minimum squared distance from source
    EntityPredicate predicate,    // param_6 - optional predicate to filter (nullptr if none)
    float maxDistSq               // param_7 - maximum squared distance from source
)
{
    int bestEntity = 0; // Return value: pointer to found entity (or 0)
    float bestDistSq = BEST_INITIAL_DISTANCE;

    if (targetType == 0) {
        return 0;
    }

    // Get player (or camera) entity for direction checks
    Entity* playerEntity = GetPlayerEntity();
    if (playerEntity == nullptr) {
        return 0;
    }

    // Compute direction from player to sourcePosition
    Vector3 dirToSource;
    dirToSource.x = sourcePosition->x - playerEntity->posX;
    dirToSource.y = sourcePosition->y - playerEntity->posY;
    dirToSource.z = sourcePosition->z - playerEntity->posZ;
    NormalizeVector(&dirToSource); // Makes it unit

    // Iterate over all entities in the container
    for (int idx = 0; idx < thisPtr->entityCount; idx++) {
        Entity* entity = thisPtr->entityArray[idx];
        if (entity == nullptr) continue;
        if (entity->activeCount == 0) continue; // Not active

        // Type check: if entityType != 0 and entityType != 0x48, then compute adjustedType
        int adjustedType = 0;
        if (entity->entityType != 0) {
            adjustedType = entity->entityType - 0x48; // subtract 0x48
        }
        // If adjustedType does not match targetType, skip
        if (adjustedType != targetType) {
            goto NEXT_ENTITY;
        }

        // If predicate is provided and returns false, skip
        if (predicate != nullptr && !predicate(entity)) {
            goto NEXT_ENTITY;
        }

        // If bRemove flag is set, and types match, remove this entity from list
        if (bRemove != 0) {
            // recalc adjustedType
            int adj = (entity->entityType != 0) ? (entity->entityType - 0x48) : 0;
            if (adj == targetType) {
                // Release reference and decrement active count
                if (entity->entityType != 0) {
                    ReleaseReference(&entity->entityType);
                    entity->entityType = 0;
                }
                entity->activeCount--;
                goto NEXT_ENTITY;
            }
        }

        // Compute squared distance from sourcePosition to entity
        float dx = sourcePosition->x - entity->posX;
        float dy = sourcePosition->y - entity->posY;
        float dz = sourcePosition->z - entity->posZ;
        float distSq = dz*dz + dy*dy + dx*dx;

        if (distSq <= maxDistSq && distSq >= minDistSq) {
            // Random chance based on entity's probabilityFactor
            float randFloat = static_cast<float>(rand()) * RAND_MAX_INVERSE;
            if (randFloat < entity->probabilityFactor) {
                // Compute direction from player to entity
                Vector3 dirToEntity;
                dirToEntity.x = entity->posX - playerEntity->posX;
                dirToEntity.y = entity->posY - playerEntity->posY;
                dirToEntity.z = entity->posZ - playerEntity->posZ;

                // Compute distance squared from player to entity
                float playerDistSq = dirToEntity.x*dirToEntity.x + dirToEntity.y*dirToEntity.y + dirToEntity.z*dirToEntity.z;

                // Check if within getter's max distance
                if (playerDistSq <= entity->maxGetterDistSq) { // Note: original checks <= and ==, simplified
                    // Check if within best so far
                    if (playerDistSq <= bestDistSq) { // Actually original checks <= playerDistSq (??) and then <= bestDistSq
                        // Compute dot product with normalized direction
                        NormalizeVector3(&dirToEntity);
                        float dot = dirToSource.x * dirToEntity.x + dirToSource.y * dirToEntity.y + dirToSource.z * dirToEntity.z;
                        if (dot < CONE_DOT_THRESHOLD) { // If behind a certain angle
                            bestDistSq = distSq;
                            bestEntity = entity;
                            // Also there was an extra check: if playerDistSq < GETTER_MAX_DIST_SQ? Actually original: fVar7 < DAT_00d5ddec
                            // We'll include that as a condition to update best (though it seems always true once inside)
                            if (playerDistSq < GETTER_MAX_DIST_SQ) {
                                // Already set bestEntity, but original code returns immediately after updating best
                                // Actually the original returns bestEntity after the update, so we break.
                                return bestEntity; // original returns iVar2 immediately
                            }
                        }
                    }
                }
            }
        }

NEXT_ENTITY:
        continue;
    }

    return bestEntity;
}
// FUNC_NAME: NPC::computeSeparationForce
// Address: 0x00719030
// Computes a separation force (repulsion) from nearby NPCs within a squared distance threshold.
// Returns the number of neighbors found.
// param_2: squared distance threshold (sqDistThreshold)
// param_3: output vector (normalized sum of weighted repulsion directions, zero if no neighbors)

#include <cstdint> // for fixed-size types if needed, but assume standard

// Forward declarations of engine helper functions (guessed names for clarity)
float* getCurrentPosition();              // returns pointer to position struct (x at +0x30, y at +0x34, z at +0x38) – global state
void* getEntityManagerInstance();         // returns manager singleton
int* getEntityList(void* manager);        // returns head of linked list of entity nodes (struct: id at offset 0, next at offset 4)
bool isEntityValid();                     // returns true if current entity is valid (e.g., alive, same team)
void normalizeVector(float* vec);         // normalizes vector in place (assumes non-zero)

int __thiscall NPC::computeSeparationForce(float sqDistThreshold, float* outVector) {
    // Initialize output vector to zero
    outVector[0] = 0.0f;
    outVector[1] = 0.0f;
    outVector[2] = 0.0f;

    int neighborCount = 0;
    float accumX = 0.0f, accumY = 0.0f, accumZ = 0.0f;

    // Get self position (first call sets global state to "this" entity)
    float* selfPos = getCurrentPosition();
    float selfX = *(selfPos + 0x30 / sizeof(float));
    float selfY = *(selfPos + 0x34 / sizeof(float));
    float selfZ = *(selfPos + 0x38 / sizeof(float));

    // Get entity manager and its linked list of entities
    void* manager = getEntityManagerInstance();
    int** listHead = (int**)getEntityList(manager);
    int* node = *listHead; // head of linked list

    const int selfId = *(int*)(this + 0x18); // +0x18: unique ID of this NPC (e.g., entityId)

    while (node) {
        // Skip self (compare node ID with self ID)
        if (*node != selfId) {
            // Check if neighbor entity is valid (e.g., alive, not same team)
            if (isEntityValid()) {
                // Get neighbor position (global state updated to current node's entity)
                float* neighborPos = getCurrentPosition();
                float dx = *(neighborPos + 0x30 / sizeof(float)) - selfX;
                float dy = *(neighborPos + 0x34 / sizeof(float)) - selfY;
                float dz = *(neighborPos + 0x38 / sizeof(float)) - selfZ;

                float distSq = dx*dx + dy*dy + dz*dz;

                // Clamp to minimum distance to avoid division by zero / singularity
                static const float minDistSq = *reinterpret_cast<float*>(0x00d61b0c); // global constant
                if (distSq <= minDistSq) {
                    distSq = minDistSq;
                }

                if (distSq < sqDistThreshold) {
                    ++neighborCount;

                    // Weight: linear falloff from 1 at dist=0 to 0 at dist=sqDistThreshold
                    float weight = (sqDistThreshold - distSq) / sqDistThreshold;

                    // Normalize direction vector
                    float dirX = dx, dirY = dy, dirZ = dz;
                    normalizeVector(&dirX); // TODO: verify signature (in-place)

                    // Accumulate weighted repulsion direction
                    accumX += dirX * weight;
                    accumY += dirY * weight;
                    accumZ += dirZ * weight;
                }
            }
        }
        node = (int*)*(node + 1); // +0x04: next pointer in linked list
    }

    if (neighborCount > 0) {
        // Normalize the accumulated vector and store as output
        float sumX = accumX, sumY = accumY, sumZ = accumZ;
        normalizeVector(&sumX);
        outVector[0] = sumX;
        outVector[1] = sumY;
        outVector[2] = sumZ;
    }
    // else: outVector remains zero (already initialized)

    return neighborCount;
}
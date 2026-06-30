// FUNC_NAME: SpatialGrid::findEntityInCone
// Address: 0x006e6980
// Role: Performs a spatial query to find the closest entity within a cone defined from a reference point (camera position)
//        to a query position, within specified distance range, and optionally filtered by a callback.

// Known offsets:
// - this+0x20: base of spatial hash grid (array of pointers to linked lists, each cell 8 bytes)
// - entity+0x08: next pointer in linked list
// - entity+0x44: x position
// - entity+0x48: y position
// - entity+0x4c: z position
// - entity+0x8a: flags (bit 0 indicates disabled/ignored)

// Known globals:
// - DAT_00d5f6f0: initial max camera-to-entity distance squared
// - DAT_00d5fb04: dot product threshold (cosine of cone half-angle)
// - DAT_00d5ddec: distance squared from camera for early return
// - DAT_0112a960: array of neighbor cell offsets (pairs of signed bytes)

#include <cstdint>

// Forward declarations for external functions
float* getCameraPosition();                    // FUN_00471610: returns pointer to a struct with position at offsets 0x30,0x34,0x38
void normalizeVector3(float* vec);             // FUN_0056afa0: normalizes vector in place (assumed)

// Filter function type: returns 0 to exclude entity, non-zero to include
typedef int (*EntityFilter)(void* entity);

class SpatialGrid {
public:
    // Returns pointer to entity if found, 0 otherwise
    int __thiscall findEntityInCone(int bEnabled, float* queryPos, float minDistSq, EntityFilter filter, float maxDistSq) {
        int foundEntity = 0;
        float bestDistSq = DAT_00d5f6f0;   // Global max camera-entity distance threshold
        int candidateEntity = 0;

        if (!bEnabled) {
            return 0;
        }

        float* cameraInfo = getCameraPosition();  // Returns pointer to struct (e.g., CameraInfo)
        float dx = queryPos[0] - *(cameraInfo + 0x30 / sizeof(float));  // camera x at offset 0x30
        float dy = queryPos[1] - *(cameraInfo + 0x34 / sizeof(float));  // camera y at offset 0x34
        float dz = queryPos[2] - *(cameraInfo + 0x38 / sizeof(float));  // camera z at offset 0x38
        // Zero initializer for vector to normalize
        float normalizedDir[3] = { dx, dy, dz };
        normalizeVector3(normalizedDir);  // Normalize the direction from camera to query point

        // Compute grid cell index from camera position
        int cameraX = (int)*(cameraInfo + 0x30 / sizeof(float)) >> 3;
        int cameraY = (int)*(cameraInfo + 0x38 / sizeof(float)) >> 3;
        int startIndex = ((cameraY & 0x1f) << 5) | (cameraX & 0x1f);  // 5-bit row and column

        // Neighbor offset array: pairs of signed bytes. Loop until pointer reaches end (0x112a99a).
        uint8_t* neighborOffsets = (uint8_t*)&DAT_0112a960;
        while ((uintptr_t)neighborOffsets < 0x112a99a) {
            int rowOffset = (signed char)neighborOffsets[1];  // row offset
            int colOffset = (signed char)neighborOffsets[0];  // column offset

            // Compute cell index with wrapping (5 bits)
            int cellIndex = ((rowOffset * 0x20 + startIndex) & 0x3e0) | ((colOffset + startIndex) & 0x1f);
            // Each cell is 8 bytes, so multiply by 8
            int* cellPtr = (int*)((uint8_t*)this + 0x20) + cellIndex * 2;  // int* access, each cell is 8 bytes = 2 ints
            int entity = *cellPtr;  // First entity pointer in cell

            while (entity != 0) {
                // Check if entity is enabled (flag bit 0 is clear)
                if ((*(uint8_t*)(entity + 0x8a) & 1) == 0) {
                    // Check filter callback if provided
                    if (filter == 0 || filter((void*)entity) != 0) {
                        float ex = *(float*)(entity + 0x44);
                        float ey = *(float*)(entity + 0x48);
                        float ez = *(float*)(entity + 0x4c);

                        float dxEntity = queryPos[0] - ex;
                        float dyEntity = queryPos[1] - ey;
                        float dzEntity = queryPos[2] - ez;
                        float distSq = dxEntity * dxEntity + dyEntity * dyEntity + dzEntity * dzEntity;

                        if (distSq <= maxDistSq && minDistSq <= distSq) {
                            // Check if entity lies within cone from camera to query point
                            float vecToEntityDX = ex - *(cameraInfo + 0x30 / sizeof(float));
                            float vecToEntityDY = ey - *(cameraInfo + 0x34 / sizeof(float));
                            float vecToEntityDZ = ez - *(cameraInfo + 0x38 / sizeof(float));
                            float cameraDistSq = vecToEntityDX * vecToEntityDX + 
                                                 vecToEntityDY * vecToEntityDY + 
                                                 vecToEntityDZ * vecToEntityDZ;

                            if (cameraDistSq <= bestDistSq) {
                                // Normalize vector from camera to entity
                                float normalizedVecToEntity[3] = { vecToEntityDX, vecToEntityDY, vecToEntityDZ };
                                normalizeVector3(normalizedVecToEntity);

                                float dot = normalizedDir[0] * normalizedVecToEntity[0] +
                                            normalizedDir[1] * normalizedVecToEntity[1] +
                                            normalizedDir[2] * normalizedVecToEntity[2];

                                if (dot < DAT_00d5fb04) {
                                    // Update best candidate
                                    candidateEntity = entity;
                                    bestDistSq = distSq;

                                    // If entity is very close to camera, return immediately
                                    if (cameraDistSq < DAT_00d5ddec) {
                                        return entity;
                                    }
                                }
                            }
                        }
                    }
                }
                entity = *(int*)(entity + 8);  // Next in linked list
            }
            neighborOffsets += 2;  // Each entry is 2 bytes
        }

        return candidateEntity;
    }

private:
    static const float DAT_00d5f6f0;  // Initial best distance squared
    static const float DAT_00d5fb04;  // Cone dot product threshold
    static const float DAT_00d5ddec;  // Camera distance for early return
    static const uint8_t DAT_0112a960[]; // Actually defined in data section
};

// Static globals (from data section, actual values unknown)
const float SpatialGrid::DAT_00d5f6f0 = 1e10f;       // Placeholder
const float SpatialGrid::DAT_00d5fb04 = -0.5f;        // Placeholder (cosine of 120°)
const float SpatialGrid::DAT_00d5ddec = 25.0f;        // Placeholder
const uint8_t SpatialGrid::DAT_0112a960[] = { /* ... */ }; // Neighbor offset table (omitted for brevity)
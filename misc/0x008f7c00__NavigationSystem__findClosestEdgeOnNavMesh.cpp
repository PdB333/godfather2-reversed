// FUNC_NAME: NavigationSystem::findClosestEdgeOnNavMesh
// Address: 0x008f7c00
// Reconstructed from Ghidra decompilation for The Godfather 2 (EARS engine)
// This function iterates over a set of navmesh edges, finds the closest one to a query point,
// and updates a result structure with the closest edge endpoints and projection point.

#include <cstdint>

// Forward declarations for called functions (stubs, not implemented)
int __fastcall FUN_0085bc80(const void* navMesh, int edgeIndex);          // Returns surface type char
int __fastcall FUN_005fd340(uint16_t something, uint32_t hash, int* out); // Hash lookup, returns something
float __fastcall FUN_0084cb90(const float* fromPos, const float* queryPos, const float* vertexPos, uint64_t* outPoint, int flag); // Distance to segment
float __fastcall FUN_004a0b00(const float* fromPos, const float* dir, const float* vertexPos, const float* constant); // Dot product / angle
void __fastcall FUN_0043a210(float* vec, float* outVec); // Normalize vector

// Global constants from data section
extern float DAT_00d6112c;   // Squared distance threshold for early out
extern float _DAT_00d813ac;  // Unknown threshold (float reinterpreted as int?)
extern float DAT_00e44680;   // Bitmask for float operations
extern float DAT_00e449b4;   // Default angle threshold?
extern float DAT_00e44564;   // Another angle constant
extern float DAT_00e445a4;   // Dot product constant
extern float DAT_00d5f1a0;   // Weight/scale factor
extern float DAT_00d812a4;   // Some constant for angle calculation

// Structure for the query point (param_3)
struct NavMeshQueryPoint {
    float x, y, z;            // +0x00  Query position
    // Padding to align? Actually in the code, the short and byte are accessed at offsets 16 and 20 from start (float* +4 and +5)
    short startEdgeIndex;     // +0x10 (byte offset 16) 
    uint8_t edgeCount;        // +0x14 (byte offset 20)
    // Likely more padding
};

// Structure for the result (param_1, this)
struct EdgeQueryResult {
    // Unknown vtable or base at +0x00? Positions start at +0x04
    float x;                  // +0x04  Query object's x
    float y;                  // +0x08 
    float z;                  // +0x0C 
    float dirX;               // +0x10  direction vector
    float dirY;               // +0x14
    float dirZ;               // +0x18
    const void* navMesh;      // +0x1C  NavMesh pointer
    const float* closestEdgeA; // +0x20  Pointer to vertex A of closest edge
    const float* closestEdgeB; // +0x24  Pointer to vertex B of closest edge
    float closestDistance;    // +0x28  Minimum distance found
    float closestPointAx;     // +0x2C  Stored as double? Actually first 8 bytes of vertex A
    float closestPointAy;     // +0x30
    float closestPointAz;     // +0x34
    float closestPointBx;     // +0x38
    float closestPointBy;     // +0x3C
    float closestPointBz;     // +0x40
    float projectionX;        // +0x44  Closest point on edge (from FUN_0084cb90)
    float projectionY;        // +0x48
    float projectionZ;        // +0x4C? Actually local_c is undefined8, so maybe double?
    // +0x50? Then +0x51 for allowedSurfaceType? We'll represent as char at +0x51
    char allowedSurfaceType;  // +0x51
    // ... 
};

// Actual reconstructed function
int __thiscall EdgeQueryResult::findClosestEdgeOnNavMesh(
    const void* navMesh,           // param_2
    const NavMeshQueryPoint* query // param_3
)
{
    float dx = this->x - query->x;
    float dy = this->y - query->y;
    float dz = this->z - query->z;
    float distSq = dx*dx + dy*dy + dz*dz;

    // Early out if the object is too far from the query point
    if (DAT_00d6112c <= distSq) {
        return 1;
    }

    // Another early out: check something with the Y component (maybe vertical distance)
    float diffY = this->y - query->y;
    // Reinterpret float as uint32 for bitwise operation (looks like an optimization)
    uint32_t bits = reinterpret_cast<uint32_t&>(diffY);
    if (_DAT_00d813ac <= static_cast<float>(bits & reinterpret_cast<uint32_t&>(DAT_00e44680))) {
        return 0;
    }

    uint8_t edgeCount = query->edgeCount;
    float bestAngle = DAT_00e449b4;  // Initial angle threshold
    uint32_t i = 0;

    if (edgeCount != 0) {
        do {
            // Calculate index into the edge index buffer
            int startIndex = query->startEdgeIndex + static_cast<short>(i);
            int edgeIndex = startIndex * 0x10 + *(int*)((uint8_t*)navMesh + 0x24); // offset into index array with stride 16
            const float* vertexPos = (const float*)( *(int*)((uint8_t*)navMesh + 0x20) + (uint32_t)*(uint16_t*)(edgeIndex + 4) * 0x24 );

            char surfaceType = FUN_0085bc80(navMesh, edgeIndex);
            if (surfaceType != this->allowedSurfaceType) {
                return 0; // Surface type mismatch
            }

            int unknownValue = 0;
            int* unknownPtr = nullptr;
            char hashResult = FUN_005fd340(*(uint16_t*)(edgeIndex + 8), 0xf7276be5, &unknownValue);

            // If the hash lookup returns non-zero and points to valid data, skip this edge? 
            if (!((hashResult == 0) || (unknownPtr == nullptr) || (unknownValue == 0) || 
                  (*(char*)(unknownValue + 6) != 0x02) || (*unknownPtr == 0))) {
                // This edge has the obstacle property? Skip the normal distance calculation
                // Actually the condition skips the body (fVar7 calculation) if true
                // So we invert the condition: if the edge is considered an obstacle, skip it.
                // So we continue if ! (obstacle condition)
            } else {
                // Compute distance from query position to the edge segment
                uint64_t projection; // local_c
                float edgeDistance = FUN_0084cb90(this->x, query->x, vertexPos, &projection, 1);
                if (edgeDistance <= this->closestDistance) {
                    // Compute dot product: direction from this object to vertex along its facing direction
                    float dot = FUN_004a0b00(this->x, this->dirX, vertexPos, &DAT_00d812a4);
                    bool isBehind = false;
                    if (dot < 0.0f) {
                        if (bestAngle == DAT_00e449b4) {
                            bestAngle = DAT_00e44564 - dot;
                        }
                        if (dot < bestAngle) {
                            isBehind = true;
                            dot = bestAngle; // Clamp dot
                        }
                    }
                    // Weighted distance using dot product
                    float weightedDist = (DAT_00e445a4 - dot) * DAT_00d5f1a0 + edgeDistance;
                    if (weightedDist < this->closestDistance) {
                        // Compute vector from query to vertex (or vertex to query) depending on direction
                        float vecX, vecY, vecZ;
                        if (isBehind) {
                            vecX = query->x - vertexPos[0];
                            vecY = query->y - vertexPos[1];
                            vecZ = query->z - vertexPos[2];
                        } else {
                            vecX = vertexPos[0] - query->x;
                            vecY = vertexPos[1] - query->y;
                            vecZ = vertexPos[2] - query->z;
                        }
                        // Normalize the vector
                        FUN_0043a210(&vecX, &vecX);

                        // Check dot product with the object's facing direction
                        float normalDot = this->dirX * vecX + this->dirY * vecY + this->dirZ * vecZ;
                        bool isFacing = normalDot >= 0.0f;

                        // Store the edge vertices and projection based on orientation
                        if (isBehind) {
                            if (isFacing) {
                                goto store_normal; // label
                            }
                            // Store reversed order: pfVar1 first, then query
                            this->closestEdgeA = vertexPos;
                            this->closestEdgeB = query->x;
                            *(uint64_t*)&this->closestPointAx = *(uint64_t*)vertexPos; // copy x,y as double
                            this->closestPointAz = vertexPos[2];
                            *(uint64_t*)&this->closestPointBx = *(uint64_t*)query; // query position x,y
                            this->closestPointBz = query->z;
                        } else {
                            if (isFacing) {
                                // Store normal order: query first, vertex second
                                this->closestEdgeB = vertexPos;
                                this->closestEdgeA = query->x;
                                *(uint64_t*)&this->closestPointBx = *(uint64_t*)vertexPos;
                                this->closestPointBz = vertexPos[2];
                                *(uint64_t*)&this->closestPointAx = *(uint64_t*)query;
                                this->closestPointAz = query->z;
                            } else {
                                goto store_reverse; // label store reversed
                            }
                        }
store_normal:
                        // Original label (in the code, the normal storage case)
                        this->closestEdgeB = vertexPos;
                        this->closestEdgeA = query->x;
                        *(uint64_t*)&this->closestPointBx = *(uint64_t*)vertexPos;
                        this->closestPointBz = vertexPos[2];
                        *(uint64_t*)&this->closestPointAx = *(uint64_t*)query;
                        this->closestPointAz = query->z;
                        // Actually original assembly had two paths; simplified to match logic
                    }
                }
            }

            i++;
        } while (i < edgeCount);
    }

    return 0; // No valid edge found
}
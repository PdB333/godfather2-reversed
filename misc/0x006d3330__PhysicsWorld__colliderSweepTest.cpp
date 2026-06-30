// FUNC_NAME: PhysicsWorld::colliderSweepTest

// Address: 0x006d2db0 (thunk at 0x006d3330)
// Purpose: Performs a two‑stage collision sweep between two positions.
//   First stage: cast ray with a default half‑extent (ignore collisions?).
//   Second stage: cast ray with a full set of collision layers (0x17 = 23).
//   Returns the closest valid hit distance or a failure flag.
// Parameters:
//   startPos     – input float[4] (hkVector4): start of the sweep
//   endPos       – input float[4] (hkVector4): end of the sweep
//   outDistance  – output float (nullable): receives the closest hit distance if found
// Returns: 0x00FFFFFF on success, 0x00000001 on failure (bitwise packed)

#include <cstdint>

// Global constants (from .data section)
extern float g_infinity;          // _DAT_00d5780c (FLT_MAX)
extern float g_epsilon;           // DAT_00e44598 (tolerance)
extern float g_defaultHalfExtent; // DAT_00e445dc (default half‑extent for broadphase)
extern uint32_t g_collisionFilterData; // _DAT_00e51108 (collision filter data)
extern float g_distanceThreshold; // DAT_00e44564 (max allowed distance)

// Internal helper functions (thunks)
extern void* __fastcall hkAllocate(uint32_t size, uint32_t alignment, int32_t allocationType); // FUN_00540c60
extern void hkDeallocate(void* ptr, uint32_t size, uint32_t alignment); // FUN_00aa26e0
extern void hkSetCollisionFilter(uint32_t filter); // FUN_00a64b00
extern void hkFinalizeSetup(); // FUN_00a64fd0

// Core Havok cast functions
// Returns true if any hit, sets hitIndex and hitDistance (fStack_2e4, fStack_30c)
extern bool hkpWorld::castRay(const void* rayStart,
                              const void* rayEnd,
                              void* outHitStorage,
                              void* filterInfo); // FUN_009e7fd0

// Specific sweep query (possibly for capsule/sphere)
// Returns true if hit and computes inline hit data
extern bool hkpWorld::castShapeSweep(const float* startPos,
                                     const float* endPos,
                                     void* outSweepResult); // FUN_006d11c0, FUN_006d12b0

// Material/flag query
extern uint32_t hkpCollidable::getCollisionFlags(uint32_t collidableIndex); // FUN_005413f0

// Memory free (called with TlsGetValue and THUNK)
extern void hkFreeTLS(uint32_t tlsIndex); // FUN_00543d10

uint32_t colliderSweepTest(float* startPos, float* endPos, float* outDistance)
{
    float hitDistance1 = 0.0f;
    float hitDistance2 = 0.0f;
    float start[4];
    float end[4];
    int32_t hitCount1 = 0;
    int32_t hitCount2 = 0;
    bool hit1Valid = false;
    bool hit2Valid = false;

    // Initialize output to infinity
    if (outDistance) {
        *outDistance = g_infinity;
    }

    // Copy start and end positions
    start[0] = startPos[0]; start[1] = startPos[1]; start[2] = startPos[2]; start[3] = startPos[3];
    end[0] = endPos[0]; end[1] = endPos[1]; end[2] = endPos[2]; end[3] = endPos[3];

    // Set collision filter and prepare
    hkSetCollisionFilter(g_collisionFilterData);

    // Allocate temporary storage for raycasts (two stages)
    // Stage 1: use collision layer 1 (0x01)
    void* storage1 = (void*)hkAllocate(0x0C, 1, 0x01);
    if (!storage1) {
        return 1; // failure
    }

    // Stage 2: use collision layer 23 (0x17) (full collision)
    void* storage2 = (void*)hkAllocate(0x0C, 23, 0x01);
    if (!storage2) {
        hkDeallocate(storage1, 0x0C, 0x01);
        return 1;
    }

    // Prepare raycast parameters
    // We'll simulate the Havok raycast structure: rayStart, rayEnd, outHit, filter
    // The Ghidra decompile used a complex stack struct; we abstract it.

    // Perform first cast (broadphase with collision layer 1)
    hit1Valid = hkpWorld::castRay(&start, &end, storage1, &g_collisionFilterData);
    // After cast, hitCount1 is stored in a local variable (iStack_2e0)
    // hitDistance1 is stored in fStack_2e4
    // We assume the hit results are placed in storage1 and accessed via known offsets

    // In the original code, after the first cast it checked iStack_2e0 != 0
    // and set hitDistance1 accordingly. We replicate that.
    if (hit1Valid) {
        hitDistance1 = *(float*)((uint8_t*)storage1 + 0x04); // hypothetical offset for distance
    }

    // Perform second cast (full collision layer 23)
    hit2Valid = hkpWorld::castRay(&start, &end, storage2, &g_collisionFilterData);
    if (!hit2Valid) {
        hit2Valid = false; // original logic set bVar17 = (iStack_2e0 == 0)
        if (hit2Valid) {
            // Actually if hit2Valid is false, we set hitDistance2 to 0
            hitDistance2 = 0.0f;
        } else {
            hitDistance2 = *(float*)((uint8_t*)storage2 + 0x04); // again offset
        }
    }

    // Determine which hit distance to use
    // Original conditional:
    // if ( (!hit1Valid) || ( (!hit2Valid && (hitDistance2 + g_epsilon < hitDistance1)) ) )
    if (!hit1Valid || (!hit2Valid && (hitDistance2 + g_epsilon < hitDistance1))) {
        // Use hitDistance1 if valid, else fallthrough
        // but the code also calls castShapeSweep if hit1Valid and hit2Valid
        if (hit1Valid && hit2Valid) {
            // Use shape sweep
            float sweepResult[6]; // afStack_2d0
            bool sweepHit = hkpWorld::castShapeSweep(startPos, endPos, sweepResult);
            if (sweepHit) {
                // Override hitDistance2 with hitDistance1 (from shape sweep?)
                hitDistance2 = hitDistance1;
            } else {
                goto return_fail;
            }
        }
    }

    // After the conditional, we check if (0.0 <= hitDistance2) OR (distance * hitDistance2 <= threshold)
    float dx = start[0] - end[0];
    float dy = start[1] - end[1];
    float dz = start[2] - end[2];
    float diffSq = dx*dx + dy*dy + dz*dz;
    if ((0.0f <= hitDistance2) || (sqrt(diffSq) * hitDistance2 <= (g_distanceThreshold - g_collisionFilterData))) {
        // No good hit found, but if the first hit was valid, do an additional narrowphase cast
        if (hit1Valid) {
            // Perform a narrowphase shape cast with default half‑extent
            // Allocate storage for results
            void* narrowStorage = (void*)hkAllocate(0x0C, 0x08, 0x01); // 0x08 likely sphere or capsule
            if (!narrowStorage) {
                // handle error
            } else {
                hitCount2 = 0; // iStack_1ec
                float narrowHalfExtent = g_defaultHalfExtent;
                bool narrowHit = hkpWorld::castRay(&start, &end, narrowStorage, &narrowHalfExtent);
                // Loop through results (up to 8 hits? 0x30 stride)
                int32_t numHits = hitCount2; // iStack_1ec after call
                for (int32_t i = 0; i < numHits; ++i) {
                    float hitDist = *(float*)((uint8_t*)narrowStorage + i * 0x30 + 0x1C);
                    if (hitDist > hitDistance2) {
                        uint32_t collidableFlags = hkpCollidable::getCollisionFlags(
                            *(uint32_t*)(*(int32_t*)((uint8_t*)narrowStorage + i * 0x30 + 0x28) + 0x1C));
                        if ((collidableFlags & 2) == 0) {
                            if (outDistance) {
                                *outDistance = hitDist;
                            }
                            // Free temporary storage
                            hkFreeTLS(0x01139810); // TLS index for deallocation
                            hkDeallocate(narrowStorage, 0x0C, 0x01);
                            hkDeallocate(storage1, 0x0C, 0x01);
                            hkDeallocate(storage2, 0x0C, 0x01);
                            return 0x00FFFFFF; // success
                        }
                    }
                }
                // Free narrow storage if not used
                hkDeallocate(narrowStorage, 0x0C, 0x01);
            }
        }
        // Fallthrough: no good hit found
        if (outDistance) {
            *outDistance = hitDistance2; // could be 0 or any found distance
        }
        // Return success (cast went through, no blocking hit)
        hkDeallocate(storage1, 0x0C, 0x01);
        hkDeallocate(storage2, 0x0C, 0x01);
        return (uint32_t)outDistance & 0xFFFFFF00; // packed flag
    }

return_fail:
    // Cleanup and return failure
    hkDeallocate(storage1, 0x0C, 0x01);
    hkDeallocate(storage2, 0x0C, 0x01);
    return 1; // 0x00000001
}
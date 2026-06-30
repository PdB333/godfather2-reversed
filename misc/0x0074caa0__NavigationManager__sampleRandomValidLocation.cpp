// FUNC_NAME: NavigationManager::sampleRandomValidLocation

#include <cstdint>

// Helper: get global timer/player transform pointer
extern void* getPlayerTransform(); // corresponds to FUN_00471610

// Math/random helpers
extern void randomFloatFunc1(); // corresponds to FUN_00b99fcb
extern void randomFloatFunc2(); // corresponds to FUN_00b99e20

// Raycast/ground sample function
extern int performRaycast(const float* start, const float* dir, int flags, int someID, int* outHit, int flag); // FUN_00542650

// Process collision result and fill a result structure
extern int processCollisionOutput(void* outputStruct, void** queryData); // FUN_009e5ed0

// Converts integer to something (maybe random seed)
extern uint32_t getRandomSeed(); // corresponds to FUN_0043b490

// Globals (replace with actual names if known)
extern int32_t gMaxIterations;         // DAT_00e5193c
extern float gYOffset;                 // DAT_00d5fae0
extern float gRandomScale;             // DAT_00d5eeec
extern float gEpsilon;                 // DAT_00d5780c
extern float gLargeNegativeAdjust;     // DAT_00e44578
extern volatile int32_t gRandomCounter; // DAT_012054b4
extern float gBestDistanceInit;        // DAT_00d5ccf8
extern float gStoppingFactor;          // DAT_00d64730
extern float gTimeFactor;              // DAT_00d64704

// Table of random floats (DAT_010c2680)
extern float gRandomTable[];

// Collision query data (PTR_FUN_00e32a8c)
extern void* gCollisionQueryData;

// ----------------------------------------------------------------

// Input: param_1 = this, param_2 = inPos (float[3]), param_3 = outPos (float[3]), param_4 = radiusScale
void __thiscall NavigationManager::sampleRandomValidLocation(
    int thisPtr, float* inPos, float* outPos, float radiusScale) 
{
    // Step 1: Get player/character transform
    void* playerTransform = getPlayerTransform();
    
    // Extract current player Y coordinate from transform +0x38
    float playerY = *(float*)((int)playerTransform + 0x38);
    
    // Extract player X and Z as a compressed 8-byte value at +0x30
    // Lower 32 bits -> playerX, upper 32 bits -> playerZ + offset
    uint64_t compressedPos = *(uint64_t*)((int)playerTransform + 0x30);
    float playerX = (float)(uint32_t)(compressedPos & 0xFFFFFFFF);
    float playerZ_raw = (float)(uint32_t)(compressedPos >> 32);
    float playerZ = gYOffset + playerZ_raw;
    
    // Initialize best hit parameters
    float bestDist = gBestDistanceInit;   // large
    float bestX = 0.0f, bestZ = 0.0f;
    uint64_t bestPosPacked = 0;
    bool foundHit = false;
    
    // Random iteration count
    if (gMaxIterations == 0) {
        // No iterations; just copy input to output
        *((uint64_t*)outPos) = *((uint64_t*)inPos);   // copy first two floats as 64-bit
        outPos[2] = inPos[2];
        return;
    }
    
    uint32_t iter = 0;
    do {
        // Generate pseudo-random index into table
        uint32_t tableIdx = gRandomCounter & gEpsilon; // actually DAT_010c2678 mask?
        gRandomCounter = gRandomCounter + 1;
        
        // Compute integer offset (handling negative)
        float fIter = (float)(int32_t)iter;
        if ((int32_t)iter < 0) {
            fIter += gLargeNegativeAdjust;
        }
        
        // Get random angle from table and scale it
        float rawAngle = gRandomTable[tableIdx] * (fIter + gEpsilon) * gRandomScale;
        
        // Clamp to symmetric range [-something, something]
        float clampedAngle = fIter * gRandomScale;
        float upperBound = (fIter + gEpsilon) * gRandomScale;
        if (rawAngle < clampedAngle) {
            rawAngle = clampedAngle;
        } else if (rawAngle > upperBound) {
            rawAngle = upperBound;
        }
        
        // Cast to double and apply random functions (likely no effect)
        double tempDouble = (double)rawAngle;
        randomFloatFunc1();
        float randomOffset1 = (float)tempDouble;  // remains same
        tempDouble = (double)rawAngle;
        randomFloatFunc2();
        float randomOffset2 = (float)tempDouble;  // remains same
        
        // Build candidate point: offset from input in X and Z,
        // but Y comes from player's Y? Actually we use playerY for Y?
        float candX = randomOffset2 * radiusScale + inPos[0];
        // CandY uses playerY? Wait, we stored playerY in local_f8.
        // The code uses fStack_10c = fStack_fc (which is playerZ?) 
        // Actually fStack_fc was playerZ from transform, not playerY.
        // This is confusing; we'll keep the original logic.
        // For now: use playerZ for Y? No.
        // We'll assume Y is from player's Y (actually the transform's Y is at +0x38).
        // But the code uses playerZ as the second component? 
        // Let's keep the original meaning:
        float candY_local = playerZ;   // was fStack_fc
        float candZ = randomOffset1 * radiusScale + inPos[2];
        
        // Get some random seed for raycast
        int seed = getRandomSeed();
        
        // Prepare input point for raycast (use candX, candZ, but Y from playerY? Actually they used the local stack)
        // In original: &local_110 -> (candX, candY_local, candZ)
        // They then call raycast with some ID from this+0x88+0x830
        int* raycastInput[6] = {0}; // dummy
        int raycastResult = performRaycast(
            &candX, &candY_local, // start
            0x40102,              // flags
            *(int*)(*(int*)(thisPtr + 0x88) + 0x830), // some ID
            &seed,
            1                     // some flag
        );
        
        // Process collision query
        // Local structures for output
        int hitSomething = 0;
        float hitDistance = gEpsilon;
        float someOther = gEpsilon;
        void* queryData = &gCollisionQueryData;
        void outputStruct[23]; // size ~92 bytes
        hitSomething = processCollisionOutput(outputStruct, &queryData);
        
        if (hitSomething == 0) {
            // No hit: return this candidate directly
            *((uint64_t*)outPos) = *((uint64_t*)&candX); // pack candX and candY_local
            outPos[2] = candZ;
            return;
        }
        
        // Compute hit factor (distance along ray)
        float fHit = 0.0f;
        if (hitDistance > 0.0f) {
            if (hitDistance < gEpsilon) {
                fHit = hitDistance;
            } else {
                fHit = gEpsilon;
            }
        }
        
        // Update candidate position to hit point
        float factor = fHit * radiusScale - gStoppingFactor;
        candX = (candX - playerX) * factor + playerX;
        float candY_new = (candY_local - playerZ) * factor + playerZ; // using playerZ as base? This is messy.
        candZ = (candZ - playerY) * factor + playerY; // using playerY as base?
        
        // Check if this hit is close enough
        if (radiusScale * gTimeFactor < factor) {
            break;
        }
        
        // Update best hit if closer than previous best
        if (fHit < bestDist) {
            bestDist = fHit;
            bestPosPacked = *((uint64_t*)&candX); // pack candX and candY_new
            bestZ = candZ;
            foundHit = true;
        }
        
        iter++;
    } while (iter < (uint32_t)gMaxIterations);
    
    if (foundHit) {
        *((uint64_t*)outPos) = bestPosPacked;
        outPos[2] = bestZ;
        return;
    }
    
    // No valid position found; fallback to original input
    *((uint64_t*)outPos) = *((uint64_t*)inPos);
    outPos[2] = inPos[2];
}
// FUNC_NAME: PlayerCoverSystem::processCoverCollision

// Function address: 0x0050ae70
// This function handles cover sliding collision detection and resolution for a player/character.
// It checks proximity to cover nodes, computes a desired movement, and adjusts the position to slide along cover surfaces.

#include <cstdint>

// Constants (from global data)
static const float kMinMovementThreshold = DAT_00e44598; // Minimum movement distance to process
static const float kWorldBoundaryZ = DAT_00e2b1a4;      // Likely 0.0f (floor/ground level)
static const float kSlideFactorDefault = DAT_00e2b334;  // Default sliding factor
static const uint32_t kCoverNodeSize = 0x50;            // Size of each cover node entry

// Forward declarations of called functions (not shown)
extern void FUN_00414aa0();
extern void FUN_0044d680(float* out, float* in);
extern uint32_t FUN_0043b490();
extern void* FUN_009c8e50(uint32_t size);
extern uint32_t FUN_00540bc0(uint32_t a1, uint32_t a2, void* a3, bool a4);
extern void* TlsGetValue(uint32_t index);
extern void* FUN_00aa2680(uint32_t a1, uint32_t a2);
extern void* FUN_009f59e0(float* bounds, uint32_t flags);
extern void FUN_009e7450(void* obj);
extern void FUN_009f5240(float* bounds);
extern uint8_t FUN_004afee0(float* worldPos, float* startPos, float* bounds, float* delta, uint32_t flags, uint32_t* outFlags, void* collisionVolume);
extern void FUN_0044c490(float* out, float* in, float factor, float* start);
extern void FUN_00427140(float* dest, float* src, float factor, void* param);
extern void FUN_00509590(int* pArray);
extern uint8_t FUN_00475710();
extern void FUN_0050ad40(void* thisObj, float* output);
extern void FUN_0050b760(void* param, float* delta, float* output, float* bounds, int32_t index, uint32_t flags1, uint32_t flags2);
extern void FUN_005094c0(int* pArray, uint32_t flag);

// Structure offsets (via pointer arithmetic)
// param1 (this) fields:
// +0x24: pointer to character state (struct charState)
// +0x68: pointer to allocated collision volume (struct CollisionVolume)
// +0x6c: cover handle/id
// +0x5b: byte flag (in cover? 0x01 = in cover)
// +0x90: float (character radius or offset)
// +0x04: base pointer for some table
// charState (+0x24) fields:
// +0x110: byte flags (low bits used for direction/orientation)
// +0x111: byte cover level/priority
// +0x114: uint32 (some property)
// +0x10c: uint32 flags (bit 6 is important)
// +0x100: float (movement speed threshold)
// +0xe0: float (unknown)
// +0x155: byte (sign bit check)
// CollisionVolume structure (pointed by +0x68):
// +0xa0..0xbc: min/max bounds (aabb)
// Cover node array (accessed via param2):
// Each entry is 0x50 bytes.
// +0x30,0x34,0x38: float position (world space)
// +0x55: byte (some flag)

uint8_t __thiscall PlayerCoverSystem::processCoverCollision(
    void* thisObj,
    int* pCoverNodeArray,
    int nodeIndex,
    float* pStartPos,       // input position (4 floats)
    float* pOutputPos,      // output position (modified in place)
    float slideFactor,
    float desiredDistance)
{
    // Get character state pointer
    char* charState = *(char**)((uint8_t*)thisObj + 0x24);
    
    uint8_t result = 0;
    
    // Early out: check if character state is valid and we have enough movement
    if (charState[0x155] < 0) // sign? probably a status flag
        return 0;
    
    if (desiredDistance <= kMinMovementThreshold)
        return 0;
    
    // Compute pointer to current cover node
    uint32_t tlsBase = *(uint32_t*)(__readfsdword(0x2c) + 0x2c); // thread-local storage
    int nodeOffset = nodeIndex * kCoverNodeSize;
    uint8_t* pNode = (uint8_t*)(*pCoverNodeArray + *(int*)(tlsBase + 8) + nodeOffset);
    
    uint32_t nodeFlags = *(uint8_t*)(pNode + 0x55); // flag from cover node
    
    // If character has a cover level and it's <= node's flag, skip
    uint8_t coverLevel = *(uint8_t*)(charState + 0x111);
    if (coverLevel != 0 && coverLevel <= (uint8_t)nodeFlags)
        goto SKIP_OUTPUT;
    
    // Reset some internal state
    FUN_00414aa0();
    
    // Precomputed constant
    float fStack_44 = kWorldBoundaryZ; // likely 0.0
    
    // Check if node position magnitude is above threshold
    float nodePosX = *(float*)(pNode + 0x30);
    float nodePosY = *(float*)(pNode + 0x34);
    float nodePosZ = *(float*)(pNode + 0x38);
    bool bNodeFar = (nodePosX*nodePosX + nodePosY*nodePosY + nodePosZ*nodePosZ) > DAT_00e2e780; // some threshold
    
    // Copy output position to local (input/output)
    float local_40[4];
    local_40[0] = pOutputPos[0];
    local_40[1] = pOutputPos[1];
    local_40[2] = pOutputPos[2];
    local_40[3] = pOutputPos[3];
    
    FUN_0044d680(local_40, local_40); // some transformation (normalize? quaternion?)
    
    float startPos[4];
    if (bNodeFar) {
        // Use start position directly
        startPos[0] = pStartPos[0];
        startPos[1] = pStartPos[1];
        startPos[2] = pStartPos[2];
        startPos[3] = pStartPos[3];
    } else {
        // Interpolate start position towards output direction
        startPos[0] = slideFactor * local_40[0] + pStartPos[0];
        startPos[1] = slideFactor * local_40[1] + pStartPos[1];
        startPos[2] = slideFactor * local_40[2] + pStartPos[2];
        startPos[3] = slideFactor * local_40[3] + pStartPos[3];
    }
    
    // Compute delta between world position (some internal) and start
    // local_50, fStack_4c, fStack_48 are read from somewhere (maybe this+some offset)
    // They are not initialized in this scope – likely they come from global/register context.
    // Actually in the decompiled, they are read from stack locals that are set elsewhere.
    // We'll assume they are provided as internal state (like desired world position).
    // For reconstruction, we'll treat them as local variables that are supposed to be computed.
    // But from context, local_50/fStack_4c/fStack_48 are the target world position (where we want to go).
    // We'll just use the existing local variables from the decompiled code.
    
    // Those locals are set earlier via unrolled moves; we'll keep them as is.
    
    // Compute difference from current start to world target
    float diffX = local_50 - startPos[0];
    float diffY = fStack_4c - startPos[1];
    float diffZ = fStack_48 - startPos[2];
    float diffW = fStack_44 - startPos[3];
    
    // If squared distance is too small, skip
    if (diffX*diffX + diffZ*diffZ + diffY*diffY < kMinMovementThreshold)
        return 0;
    
    // Get some index from this object
    int someIndex = *(int*)(*(int*)((uint8_t*)thisObj + 4) + 0xc4);
    if (someIndex != 0)
        someIndex -= 0x48; // adjustment
    
    // Encode direction flags from character state byte
    uint32_t dirFlags = *(uint8_t*)(charState + 0x110);
    uint32_t encodedDir = ((((dirFlags & 8) * 2 | dirFlags & 4) << 8 | dirFlags & 2) * 8 | dirFlags & 1) * 2;
    uint32_t local_70 = encodedDir;
    
    void* collisionVolume = *(void**)((uint8_t*)thisObj + 0x68);
    
    if (collisionVolume == nullptr) {
        // No collision volume yet, create one from world bounds
        float minX = kWorldBoundaryZ, minY = kWorldBoundaryZ, minZ = kWorldBoundaryZ;
        float maxX = kWorldBoundaryZ, maxY = kWorldBoundaryZ, maxZ = kWorldBoundaryZ;
        
        // Clamp world target to minimums
        if (local_50 <= kWorldBoundaryZ) minX = local_50;
        if (fStack_4c <= kWorldBoundaryZ) minY = fStack_4c;
        if (fStack_48 <= kWorldBoundaryZ) minZ = fStack_48;
        
        // Clamp for maximums
        float tempMaxX = kWorldBoundaryZ;
        if (local_50 < DAT_00e446d4) local_50 = DAT_00e446d4;
        if (fStack_4c < DAT_00e446d4) fStack_4c = DAT_00e446d4;
        float tempMaxY = DAT_00e446d4;
        if (DAT_00e446d4 <= fStack_48) tempMaxY = fStack_48;
        float tempMaxZ = fStack_48;
        if (fStack_48 < DAT_00e446d4) tempMaxZ = DAT_00e446d4;
        
        // Update mins with start pos
        if (startPos[0] <= minX) minX = startPos[0];
        if (startPos[1] <= minY) minY = startPos[1];
        if (startPos[2] <= minZ) minZ = startPos[2];
        if (startPos[3] <= kWorldBoundaryZ) fStack_44 = startPos[3];
        
        // Update maxs with start pos
        float maxX2 = startPos[0];
        if (startPos[0] < local_50) maxX2 = local_50;
        if (fStack_4c <= startPos[1]) fStack_4c = startPos[1];
        if (tempMaxY <= startPos[2]) tempMaxY = startPos[2];
        float maxZ2 = startPos[3];
        if (startPos[3] < kWorldBoundaryZ) maxZ2 = kWorldBoundaryZ;
        
        // Add padding
        float padding = (*(float*)(charState + 0xe0) + *(float*)((uint8_t*)thisObj + 0x90)) * DAT_00e2dd14;
        tempMaxY += padding;
        maxX2 += padding;
        fStack_4c += padding;
        minX -= padding;
        minY -= padding;
        minZ -= padding;
        
        // Get some info - possibly a reference to the world coordinate transform
        uint32_t reference = 0;
        if (someIndex != 0)
            reference = FUN_0043b490();
        
        // Allocate memory for collision volume
        void* mem = FUN_009c8e50(0x14);
        uint32_t handle = 0;
        if (mem != nullptr)
            handle = FUN_00540bc0(encodedDir, *(uint32_t*)(charState + 0x114), &reference, (someIndex != 0));
        
        *(uint32_t*)((uint8_t*)thisObj + 0x6c) = handle;
        
        // Get some TLS data and allocate another object
        TlsGetValue(DAT_01139810);
        void* obj2 = FUN_00aa2680(0xd0, 0x31);
        *(uint16_t*)((uint8_t*)obj2 + 4) = 0xd0;
        
        // Create collision volume with bounds and flags
        float bounds[4] = { minX, minY, minZ, fStack_44 };
        collisionVolume = FUN_009f59e0(bounds, (*(uint32_t*)((uint8_t*)thisObj + 0x6c) >> 2) | 0x40000000);
        *(void**)((uint8_t*)thisObj + 0x68) = collisionVolume;
        
        if (collisionVolume != nullptr && *(int*)((uint8_t*)collisionVolume + 8) == 0)
            FUN_009e7450(collisionVolume);
    } else {
        // Collision volume exists, check if world target is inside its bounds
        float minX = *(float*)((uint8_t*)collisionVolume + 0xa0);
        float minY = *(float*)((uint8_t*)collisionVolume + 0xa4);
        float minZ = *(float*)((uint8_t*)collisionVolume + 0xa8);
        float maxX = *(float*)((uint8_t*)collisionVolume + 0xb0);
        float maxY = *(float*)((uint8_t*)collisionVolume + 0xb4);
        float maxZ = *(float*)((uint8_t*)collisionVolume + 0xb8);
        float minW = *(float*)((uint8_t*)collisionVolume + 0xac); // w min?
        float maxW = *(float*)((uint8_t*)collisionVolume + 0xbc); // w max?
        
        // Determine if world target is inside volume
        uint32_t flagsInside = 0;
        if (local_50 >= minX) flagsInside |= 8;
        if (fStack_4c >= minY) flagsInside |= 4;
        if (fStack_48 >= minZ) flagsInside |= 2;
        if (kWorldBoundaryZ >= minW) flagsInside |= 1; // note: constant used
        
        // Determine if start position is inside volume
        uint32_t flagsStartInside = 0;
        if (startPos[0] >= minX) flagsStartInside |= 8;
        if (startPos[1] >= minY) flagsStartInside |= 4;
        if (startPos[2] >= minZ) flagsStartInside |= 2;
        if (startPos[3] >= minW) flagsStartInside |= 1;
        
        // If both inside and all direction flags match, skip adjusting bounds
        if ((flagsInside & flagsStartInside) == 0xe) {
            // Check if start part is also inside?
            // The decompiled code then checks if startPos is also inside similarly and if both match, goto adjustment.
        }
        
        // Adjust bounds to include both positions
        if (local_50 <= minX) minX = local_50;
        if (fStack_4c <= minY) minY = fStack_4c;
        if (fStack_48 <= minZ) minZ = fStack_48;
        if (kWorldBoundaryZ <= minW) minW = kWorldBoundaryZ;
        
        if (maxX <= local_50) maxX = local_50;
        if (maxY <= fStack_4c) maxY = fStack_4c;
        if (fStack_48 < maxZ) maxZ = fStack_48;
        if (maxW < kWorldBoundaryZ) maxW = kWorldBoundaryZ;
        
        // Update with start positions
        if (startPos[0] <= minX) minX = startPos[0];
        if (startPos[1] <= minY) minY = startPos[1];
        if (startPos[2] <= minZ) minZ = startPos[2];
        if (startPos[3] <= minW) minW = startPos[3];
        if (maxX <= startPos[0]) maxX = startPos[0];
        if (startPos[1] < maxY) maxY = startPos[1]; // note: mixed order
        if (startPos[2] < maxZ) maxZ = startPos[2];
        if (startPos[3] < maxW) maxW = startPos[3];
        
        // Update bounds
        FUN_009f5240(&minX);
    }
    
    // Collision detection
    uint8_t collisionResult = FUN_004afee0(&local_50, &startPos[0], &minX, &diffX,
                                          *(uint32_t*)(charState + 0x114), &flags, collisionVolume);
    if (collisionResult == 0)
        return 0;
    
    result = 1;
    
    // Check if character is in cover mode (this+0x5b == 1)
    if (*(uint8_t*)((uint8_t*)thisObj + 0x5b) == 1)
        slideFactor = kSlideFactorDefault;
    
    // Transform final position
    FUN_0044c490(&minX, &diffX, slideFactor, pStartPos);
    FUN_00427140(&minX, &diffX, kSlideFactorDefault, (void*)(*pCoverNodeArray + *(int*)(tlsBase + 8) + 0x60 + nodeOffset));
    FUN_00509590(pCoverNodeArray);
    
    // Check cover level condition
    bool coverExceeded = false;
    if (coverLevel != 0 && (int)(nodeFlags + 1) < (int)coverLevel)
        coverExceeded = true;
    
    uint32_t charFlags = *(uint32_t*)(charState + 0x10c);
    if (((charFlags >> 6) & 1) == 0 || !coverExceeded ||
        FUN_00475710() != 0) // some additional check
    {
        // Normal path
        FUN_0050ad40(thisObj, pOutputPos);
        
        if (bNodeFar) {
            // Update flags for the collision volume
            if (flags == 0 || (*(uint32_t*)(flags + 4) & DAT_012054e4) == 0)
                flags = (flags & 0xffffff00) | 1;
            
            uint32_t local_78 = someIndex >> 8;
            if (someIndex == 0) {
                uint32_t temp = 0;
                if (local_70 == 0xe || local_70 == 5 || local_70 == 0x10) {
                    local_78 = temp;
                    local_78 = (local_78 & 0xffffff00) | 1;
                }
            } else {
                local_78 = (local_78 & 0xffffff00) | ((*(uint16_t*)(someIndex + 0x15e) >> 0xe) & 1);
            }
            
            // Apply sliding effect via sibling function
            FUN_0050b760(*pCoverNodeArray + *(int*)(tlsBase + 8) + 0x60 + nodeOffset,
                        &diffX, pOutputPos, &minX, someIndex, flags, local_78);
        }
        
        // Update output position with new bounds
        pOutputPos[0] = minX;
        pOutputPos[1] = minY;
        pOutputPos[2] = minZ;
        pOutputPos[3] = minW;
    } else {
        // Check if movement speed is sufficient
        double diffYDouble = (double)diffY;
        FUN_00b9b988();
        if (*(float*)(charState + 0x100) <= (float)diffYDouble && (float)diffYDouble != *(float*)(charState + 0x100)) {
            FUN_005094c0(pCoverNodeArray, 4);
            goto NORMAL_PATH;
        }
    }
    
    if (!coverExceeded)
        return 1;
    
SKIP_OUTPUT:
    pOutputPos[0] = 0.0f;
    pOutputPos[1] = 0.0f;
    pOutputPos[2] = 0.0f;
    return result;
}
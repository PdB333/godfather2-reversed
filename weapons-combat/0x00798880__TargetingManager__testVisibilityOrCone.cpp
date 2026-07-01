// FUNC_NAME: TargetingManager::testVisibilityOrCone
// Function: 0x00798880
// Role: Tests if a point (param_2, param_3, param_4) is within a cone/field-of-view and line-of-sight from the camera/player position.
// Uses global thresholds to determine directional flags, then casts a ray/probe to check obstruction.

extern float DAT_00d6a5c0;
extern float DAT_00d6a5b4;
extern float DAT_00d6a5bc;
extern float DAT_00d6a5b8;
extern float DAT_00d577a0;

struct Transform {
    float x, y, z; // +0x00
    // +0x20: packed double of x and y? Actually at +0x20 is (x,y) as double, +0x28 is z
    // +0x30: position x, y, z? (as separate floats)
};

// Forward declarations
void* __cdecl getCameraTransform(); // FUN_00471610 - returns pointer to camera/player transform
float __cdecl vectorMagnitudeSquared(float* vec); // FUN_0056afa0
void* __cdecl castRay(int flags, float px, float py, float pz, int unk1, int unk2); // FUN_00896b30

int __cdecl FUN_00798880(unsigned int param_1, float param_2, float param_3, float param_4) {
    int flags = 2; // base flag (e.g., "in front" default)
    
    // Get camera transform
    Transform* camTrans = (Transform*)getCameraTransform();
    
    // Extract camera forward/up direction from packed data at +0x20/+0x28
    // The double at +0x20 contains x and y as two floats (low = x, high = y)
    double packedXY = *(double*)((char*)camTrans + 0x20);
    float camForwardX = (float)(unsigned long long)packedXY;        // low dword (x)
    float camForwardY = (float)((unsigned long long)packedXY >> 32); // high dword (y)
    float camForwardZ = *(float*)((char*)camTrans + 0x28);           // z
    
    // Get target position (second call to getCameraTransform? Actually third call)
    // Note: first call used for camera, second call used for something else (maybe another transform)
    Transform* targetTrans = (Transform*)getCameraTransform();
    Transform* diffSource = (Transform*)getCameraTransform(); // third call
    // Compute vector from camera to target (assume position at +0x30)
    float dx = *(float*)((char*)diffSource + 0x30) - *(float*)((char*)targetTrans + 0x30);
    float dy = *(float*)((char*)diffSource + 0x34) - *(float*)((char*)targetTrans + 0x34);
    float dz = *(float*)((char*)diffSource + 0x38) - *(float*)((char*)targetTrans + 0x38);
    
    // Get another direction vector (possibly right or up) from second call to getCameraTransform
    Transform* secondTrans = (Transform*)getCameraTransform();
    float dirX = secondTrans->x;
    float dirY = secondTrans->y;
    float dirZ = secondTrans->z;
    
    // Compute squared distance
    float distSq = vectorMagnitudeSquared(&dx); // note: passes same pointer twice
    
    // Dot product with forward direction
    float forwardDot = dx * camForwardX + dy * camForwardY + dz * camForwardZ;
    
    // Dot product with secondary direction (up/right)
    float sideDot = dx * dirX + dy * dirY + dz * dirZ;
    
    // Determine directional flags based on thresholds
    if (forwardDot <= DAT_00d6a5c0) {
        if (forwardDot >= DAT_00d6a5b4) {
            flags = 0x40; // e.g., "behind but close"
            if (sideDot <= DAT_00d577a0) {
                flags = 0x10; // e.g., "behind left"
            }
        } else {
            flags = 0x20; // e.g., "behind far"
        }
    } else if (forwardDot < DAT_00d6a5bc) {
        if (forwardDot >= DAT_00d6a5b8) {
            if (sideDot <= DAT_00d577a0) {
                flags = 4; // e.g., "right side"
            } else {
                flags = 1; // e.g., "left side"
            }
        } else if (sideDot <= DAT_00d577a0) {
            flags = 8; // e.g., "dead right"
        } else {
            flags = 0x80; // e.g., "dead left"
        }
    }
    // else (in front, default flags=2 remains)
    
    // Cast ray/probe with chosen flags
    void* hitInfo = castRay(flags, param_4, param_2, param_3, 2, 0);
    if (hitInfo != nullptr) {
        float hitDistSq = *(float*)((char*)hitInfo + 0x14);
        // Compare squared distance (fVar6 * fVar6) with hit distance
        if (distSq <= hitDistSq && distSq != hitDistSq) {
            return 1; // visible (within line of sight)
        }
    }
    return 0;
}
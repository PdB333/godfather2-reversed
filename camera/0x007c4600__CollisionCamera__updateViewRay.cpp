// FUNC_NAME: CollisionCamera::updateViewRay
#include <cstdint>

// Forward declarations
struct Vec3f {
    float x, y, z;
};

// Static globals (initialized lazily from offset 0x1fac, 0x1fb4, 0x1fb8 of character)
static float g_fovFactor;          // +0x1fac
static float g_dampingNear;        // +0x1fb4
static float g_dampingFar;         // +0x1fb8
static int g_initFlags;            // bitmask: 1,2,4

// External globals
extern float g_timeInterpolationFactor;  // _DAT_00d5c458
extern void* g_someGlobal;               // placeholder

// Forward declarations for called functions
void computeRayDirection(CollisionCamera* cam, Vec3f* outOrigin, Vec3f* outDirection); // FUN_007c4040
void* getPrevTransform();  // FUN_00471610 (first call)
void* getCurrTransform();  // FUN_00471610 (second/third call)
uint32_t getCollisionFilter();  // FUN_0043b490
bool raycast(const Vec3f* start, const Vec3f* end, float radius, uint32_t flags, uint32_t* filter, int doStuff, int zero1, int zero2, int zero3); // FUN_0054ebf0

bool CollisionCamera::updateViewRay(int param_1, int param_2, Vec3f& rayStart, void* pCharacter) {
    // Check for null pointers
    if (!param_1 || !param_2 || !pCharacter) {
        return false;
    }
    // pCharacter + 0x3c0 is expected to be a non-null pointer (e.g., camera component)
    void* pCameraComp = *(void**)((char*)pCharacter + 0x3c0);
    if (!pCameraComp) {
        return false;
    }

    Vec3f rayDirection = {0.0f, 0.0f, 0.0f}; // local_28, local_14, etc.
    Vec3f baseOrigin = {0.0f, 0.0f, 0.0f};   // local_20, local_24, local_28? Actually local_28 is one element.

    // Compute initial ray origin and direction
    computeRayDirection(this, &rayStart, &rayDirection);

    // Interpolate between previous and current frame transforms
    void* prevTrans = getPrevTransform();
    void* curTrans  = getCurrTransform();
    Vec3f interpolatedPos;
    interpolatedPos.x = (*(float*)((char*)curTrans + 0x30) - *(float*)((char*)prevTrans + 0x30)) * g_timeInterpolationFactor + *(float*)((char*)prevTrans + 0x30);
    interpolatedPos.y = (*(float*)((char*)curTrans + 0x34) - *(float*)((char*)prevTrans + 0x34)) * g_timeInterpolationFactor + *(float*)((char*)prevTrans + 0x34);
    interpolatedPos.z = (*(float*)((char*)curTrans + 0x38) - *(float*)((char*)prevTrans + 0x38)) * g_timeInterpolationFactor + *(float*)((char*)prevTrans + 0x38);

    // Initialize static damping parameters from character offsets if not done
    if (!(g_initFlags & 1)) {
        g_fovFactor = *(float*)((char*)pCharacter + 0x1fac);
        g_initFlags |= 1;
    }
    if (!(g_initFlags & 2)) {
        g_dampingNear = *(float*)((char*)pCharacter + 0x1fb4);
        g_initFlags |= 2;
    }
    if (!(g_initFlags & 4)) {
        g_dampingFar = *(float*)((char*)pCharacter + 0x1fb8);
        g_initFlags |= 4;
    }

    // Select which damping factor to use (based on some flag from rayStart byte)
    // The original code used bStack_1 bits; here we approximate with a field from rayStart
    float damping;
    // NOTE: bStack_1 in original is likely part of rayStart's struct (e.g., at offset 1?).
    // Since we don't know the exact field, we keep the same logic.
    // Check bit 4 of some byte (maybe rayStart.y interpretation? Actually the decompiler shows bStack_1 as a local byte)
    // We'll assume it's the first byte of rayStart's padding or a flag.
    uint8_t flag = (reinterpret_cast<uint8_t*>(&rayStart)[0] >> 4) & 1; // approximate
    if (flag != 0) {
        damping = g_dampingFar;
    } else if (g_someGlobal == nullptr) { // This condition corresponds to local_c == 0? But local_c is always 0 in this path.
        damping = g_fovFactor;
    } else {
        damping = g_dampingNear;
    }

    // Combine damping with direction and add to base origin
    Vec3f newStart;
    newStart.x = rayDirection.x * damping + baseOrigin.x;
    newStart.y = rayDirection.y * damping + baseOrigin.y;
    newStart.z = rayDirection.z * damping + baseOrigin.z;

    // Override Y with current transform's Y (camera or character height)
    void* curTrans2 = getCurrTransform();
    newStart.y = *(float*)((char*)curTrans2 + 0x34);

    // Get collision filter (e.g., for raycast exclusion)
    uint32_t filter = getCollisionFilter();

    // Perform the actual raycast
    if (!raycast(&interpolatedPos, &newStart, 0.10f, 0x80000000, &filter, 1, 0, 0, 0)) {
        return false;
    }
    return true;
}
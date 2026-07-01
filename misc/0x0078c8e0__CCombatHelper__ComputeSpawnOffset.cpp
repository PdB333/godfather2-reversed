// FUNC_NAME: CCombatHelper::ComputeSpawnOffset
// Address: 0x0078c8e0
// Computes a random offset position for projectile spawn or impact based on allowed direction flags and a distance scale.
// Returns an index (0-7) indicating the chosen direction type.

#include <cstdint>

// Forward declarations of called functions (assumed from context)
extern float DAT_01205228;          // Global threshold (e.g., cooldown time)
extern float DAT_00d5ef70;          // Scale factor for directions 4,5
extern float DAT_00d5eee4;          // Scale factor for direction 3

extern bool __fastcall CheckProbability(int index); // FUN_0078c5d0 - returns true if random check passes
extern void* __fastcall GetEntity();                 // FUN_00471610 - returns pointer to some entity (overloaded)
extern void __fastcall VectorNormalize(float* vec);  // FUN_0056afa0 - normalizes 3D vector
extern float __fastcall GetDirectionAngle(int dir);  // FUN_0078c2a0 - returns angle for direction index
extern void __fastcall RotateVector(float* out, float* in, float* matrix); // FUN_004a0370 - transforms vector by matrix at offset +0x10

// Bitfield flags for allowed directions (stored at this+0x20)
enum DirectionFlags : uint8_t {
    kDirAny     = 1 << 0,  // 0x01
    kDirForward = 1 << 1,  // 0x02
    kDirSide    = 1 << 2,  // 0x04
    kDirBack    = 1 << 7,  // 0x80
};

// Return values for direction type
enum DirectionType : uint32_t {
    kDirNone    = 0,
    kDirForward = 1,
    kDirSide    = 2,
    kDirBack    = 7,
    kDirUp      = 6,   // speculative
    kDirDown    = 4,   // speculative
    kDirLeft    = 5,   // speculative
    kDirRight   = 3,   // speculative
};

uint32_t __thiscall CCombatHelper::ComputeSpawnOffset(float distance, uint32_t unused, float* outPos) {
    uint32_t dirType = 0;

    // Check cooldown timer at +0x1c against global threshold
    float& timer = *(float*)((uint8_t*)this + 0x1c);
    uint8_t& flags = *(uint8_t*)((uint8_t*)this + 0x20);

    if (timer <= DAT_01205228 && DAT_01205228 != timer) {
        flags = 0;
        timer = 0.0f;
    }

    // Only proceed if any direction is allowed (bit 0 set)
    if (flags & kDirAny) {
        // Re-check timer (redundant in original code)
        if (timer <= DAT_01205228 && DAT_01205228 != timer) {
            flags = 0;
            timer = 0.0f;
        }

        if (!(flags & kDirForward)) {
            dirType = kDirForward;
        } else if (!(flags & kDirSide)) {
            dirType = kDirSide;
        } else if (!(flags & kDirBack)) {
            dirType = kDirBack;
        } else {
            // All basic directions allowed; try specific ones via probability checks
            if (!CheckProbability(6)) {
                dirType = kDirUp;
            } else if (!CheckProbability(4)) {
                distance *= DAT_00d5ef70;
                dirType = kDirDown;
            } else if (!CheckProbability(5)) {
                distance *= DAT_00d5ef70;
                dirType = kDirLeft;
            } else if (!CheckProbability(3)) {
                distance *= DAT_00d5eee4;
                dirType = kDirRight;
            }
        }
    }

    // Get two entity positions (likely player and target or something)
    void* entityA = GetEntity();  // first call
    void* entityB = GetEntity();  // second call

    // Compute horizontal direction from entityA to entityB (y=0)
    float dx = *(float*)((uint8_t*)entityB + 0x30) - *(float*)((uint8_t*)entityA + 0x30);
    float dz = *(float*)((uint8_t*)entityB + 0x38) - *(float*)((uint8_t*)entityA + 0x38);
    float dy = 0.0f;

    float dirVec[3] = { dx, 0.0f, dz };
    VectorNormalize(dirVec);

    // Get rotation angle for chosen direction type and apply to direction vector
    float angle = GetDirectionAngle(dirType);
    void* rotationEntity = GetEntity(angle);  // overloaded: returns entity with rotation matrix
    float* rotMatrix = (float*)((uint8_t*)rotationEntity + 0x10);
    RotateVector(dirVec, dirVec, rotMatrix);

    // Compute final position: entityA position + scaled direction
    outPos[0] = dirVec[0] * distance + *(float*)((uint8_t*)entityA + 0x30);
    outPos[1] = dirVec[1] * distance + *(float*)((uint8_t*)entityA + 0x34);
    outPos[2] = dirVec[2] * distance + *(float*)((uint8_t*)entityA + 0x38);

    return dirType;
}
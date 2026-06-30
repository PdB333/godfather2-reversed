// FUNC_NAME: Projectile::update
// Address: 0x00507570
// This function updates a projectile's trajectory, checks collision against a target entity,
// and applies damage or updates visual representation.

#include <cstdint>

// Forward declarations of called functions (assumed from context)
void FUN_0044d680(float* inVec, float* outVec); // Vector transform (maybe world to local?)
void FUN_0044c4c0(float* matrix, float* inVec, float* outVec); // Matrix multiply (4x4 * vec4)
void FUN_00504ae0(); // Play impact effect/sound
void FUN_00505ef0(float x, float y, float z, uint32_t flags); // Apply damage/force
void FUN_00504400(int32_t projectile); // Remove projectile from world
int32_t FUN_00505c90(int32_t pool); // Get projectile from pool (returns pointer)
void FUN_00504980(); // Update projectile transform (position/rotation)
void FUN_005071d0(float* pos, float x, float y, float z, float w, float a, float b, float c, int32_t flags); // Debug draw

// Global constants (from data section)
extern float DAT_00e2e780; // Some threshold (e.g., max lifetime)
extern int32_t DAT_0110abe8; // Game state (7 = in-game?)
extern float DAT_01218d70; // World offset X
extern float fRam01218d74; // World offset Y
extern float fRam01218d78; // World offset Z
extern float DAT_01218d60; // Matrix element (0,0) of some transform
extern float DAT_01218d64; // Matrix element (0,1)
extern float DAT_01218d68; // Matrix element (0,2)
extern float DAT_01218d80[16]; // 4x4 matrix (projection or view?)
extern float DAT_00e2cd54; // Some scale factor
extern float DAT_00e2b1a4; // 1.0f or identity value
extern float DAT_00e44564; // 1.0f or half-extent?
extern float DAT_00e446c0; // Some force multiplier
extern float _DAT_00e44938; // Another force multiplier
extern float DAT_01218dd0; // Matrix elements for transform
extern float DAT_01218dd4;
extern float fRam01218dd8;
extern float fRam01218ddc;
extern float DAT_01218dc0;
extern float fRam01218dc4;
extern float fRam01218dc8;
extern float fRam01218dcc;
extern float DAT_01218de0;
extern float fRam01218de4;
extern float fRam01218de8;
extern float fRam01218dec;
extern float DAT_01218df0;
extern float fRam01218df4;
extern float fRam01218df8;
extern float fRam01218dfc;
extern float DAT_01218e00; // Matrix for miss update
extern float DAT_01218e10;
extern float fRam01218e04;
extern float fRam01218e08;
extern float fRam01218e0c;
extern float fRam01218e14;
extern float fRam01218e18;
extern float fRam01218e1c;
extern float DAT_01218e20;
extern float fRam01218e24;
extern float fRam01218e28;
extern float fRam01218e2c;
extern float DAT_01218e30;
extern float fRam01218e34;
extern float fRam01218e38;
extern float fRam01218e3c;
extern float DAT_01218e42; // Some constant (e.g., 1.0f)
extern float DAT_01218dd4; // Duplicate? Used in both branches

// Structure for projectile data (inferred from offsets)
struct Projectile {
    // +0x00: unknown
    // +0x08: int32_t boneIndex? (used to index into some array)
    // +0x14: unknown
    // +0x20: int32_t* pFlagsAndData; // pointer to a structure with flags and vectors
    // +0x24: int32_t* pDebugDrawData; // pointer to debug draw data (or null)
    // +0x3c: uint8_t isActive; // 0 = inactive, 1 = active
    // +0x3d: uint8_t hasHit; // 0 = no hit, 1 = hit
    // +0x40: int32_t hitEntity; // entity that was hit (from +0x98)
    // +0x44: float unknown;
    // +0x48: float speedScale; // multiplier for speed
    // +0x4c: float damageMultiplier; // multiplier for damage
    // +0x50: float anotherMultiplier;
    // +0x54: float hitPointX; // world space hit point
    // +0x58: float hitPointY;
    // +0x5c: float hitPointZ;
    // +0x60: float hitNormalX; // normal at hit point
    // +0x64: float hitNormalY;
    // +0x68: float forceX; // impulse force
    // +0x6c: float forceY;
    // +0x70: float positionX; // current world position
    // +0x74: float positionY;
    // +0x78: float positionZ;
    // +0x7c: float lifetime; // remaining lifetime
    // +0x80: float velocityX; // current velocity
    // +0x84: float velocityY;
    // +0x88: float velocityZ;
    // +0x8c: float speed; // magnitude of velocity?
    // +0x90: unknown
    // +0x94: float maxLifetime; // initial lifetime
    // +0x98: int32_t* pTargetEntity; // entity to check collision against
};

// Structure for projectile flags/data (from iVar4)
struct ProjectileData {
    // +0x10: float speed; // initial speed
    // +0x14: uint32_t flags; // behavior flags
    // +0x1c: float mass; // mass for impulse calculation
    // +0x20: float directionX; // initial direction (normalized)
    // +0x24: float directionY;
    // +0x28: float directionZ;
    // +0x30: float offsetX; // offset from shooter
    // +0x34: float offsetY;
    // +0x38: float offsetZ;
    // +0x48: float damage; // base damage
    // +0x4c: uint32_t damageType; // damage type flags
};

// Structure for target entity (param_2)
struct TargetEntity {
    // +0x144: float height; // some height threshold
    // +0x16c: uint32_t boneCount; // number of bones/hitboxes
    // +0x170: BoneData* bones; // array of bone data (size boneCount * 0x38)
};

struct BoneData {
    // +0x00: unknown
    // +0x02: uint16_t width; // half-width?
    // +0x04: uint16_t height; // half-height?
    // +0x08: float matrix[16]; // bone transform?
};

int32_t Projectile::update(Projectile* this_, TargetEntity* target) {
    float lifetime = *(float*)(this_ + 0x94); // maxLifetime
    ProjectileData* data = *(ProjectileData**)(this_ + 0x20);
    float initialDirX = *(float*)(data + 0x20);
    float initialDirY = *(float*)(data + 0x24);
    float initialDirZ = *(float*)(data + 0x28);

    // Check if lifetime is above threshold
    if (DAT_00e2e780 <= lifetime) {
        float currentLifetime = lifetime; // will be modified

        if (DAT_0110abe8 == 7) { // In-game state
            // Get bone transform from some global array (FS segment)
            int32_t boneIndex = *(int32_t*)(this_ + 0x08);
            float* boneMatrix = (float*)(*(int32_t*)(*(int32_t*)(*(int32_t*)(__readfsdword(0x2c)) + 8) + 0x80) + boneIndex * 0x38);
            // boneMatrix is a 4x4 matrix? Actually we only use first 4 floats as position and one more
            float posX = boneMatrix[0];
            float posY = boneMatrix[1];
            float posZ = boneMatrix[2];
            float posW = boneMatrix[3]; // Actually the 4th element (scale?)

            // If flags indicate no offset, add initial offset
            if ((*(uint32_t*)(data + 0x14) & 6) == 0) {
                posX += *(float*)(data + 0x30);
                posY += *(float*)(data + 0x34);
                posZ += *(float*)(data + 0x38);
            }

            // Subtract world offset (camera position?)
            posX -= DAT_01218d70;
            posY -= fRam01218d74;
            posZ -= fRam01218d78;

            *(uint8_t*)(this_ + 0x3d) = 1; // Mark as hit

            float speed = *(float*)(data + 0x10);
            if (speed != 0.0f) {
                // Check if direction is towards the target (dot product with initial direction)
                float dot = posX * DAT_01218d60 + posY * DAT_01218d64 + posZ * DAT_01218d68;
                if (0.0f <= dot) {
                    float tempVec[4];
                    tempVec[0] = posX;
                    tempVec[1] = posY;
                    tempVec[2] = posZ;
                    tempVec[3] = posW;
                    FUN_0044d680(tempVec, &posX); // Transform vector (maybe to local space?)
                    posX += speed * posX; // Actually the output is stored in local variables
                    posY += speed * (*(float*)(&posX + 4)); // This is messy; need to see the actual output
                    posZ += speed * (*(float*)(&posX + 8));
                }
            }

            // Transform by a matrix (projection?)
            float inVec[4] = {posX, posY, posZ, posW};
            float outVec[4];
            FUN_0044c4c0(&DAT_01218d80, inVec, outVec);
            posX = outVec[0];
            posY = outVec[1];
            posZ = outVec[2];
            posW = outVec[3];

            float scale = DAT_00e2cd54;
            // Check if the transformed Z is less than target's height
            if (outVec[2] < *(float*)(target + 0x144)) {
                // Get bone data from target
                BoneData* boneData;
                if (*(uint32_t*)(target + 0x16c) < 0x1000) {
                    boneData = (BoneData*)(&DAT_011a0f28 + *(uint32_t*)(target + 0x16c) * 0x38);
                } else {
                    boneData = nullptr;
                }

                // Perform matrix multiplication for velocity update (using some matrix)
                float vx = outVec[0];
                float vy = outVec[1];
                float vz = outVec[2];
                float vw = outVec[3];
                // This is a 4x4 matrix multiply with the velocity vector
                float newX = vx * DAT_01218dd0 + vy * DAT_01218dc0 + vz * DAT_01218de0 + DAT_00e2b1a4 * DAT_01218df0;
                float newY = vx * DAT_01218dd4 + vy * fRam01218dc4 + vz * fRam01218de4 + DAT_00e2b1a4 * fRam01218df4;
                float newZ = vx * fRam01218dd8 + vy * fRam01218dc8 + vz * fRam01218de8 + DAT_00e2b1a4 * fRam01218df8;
                float newW = vx * fRam01218ddc + vy * fRam01218dcc + vz * fRam01218dec + DAT_00e2b1a4 * fRam01218dfc;

                float invW = DAT_00e2b1a4 / newW;
                posX = invW * newX;
                posY = invW * newY;
                posZ = invW * newZ;
                posW = invW * newW;

                float boneWidth = (float)*(uint16_t*)(boneData + 2);
                float boneHeight = (float)*(uint16_t*)(boneData + 4);

                // If flag 0x800 is set, force Z to 1.0
                if ((*(uint32_t*)(data + 0x14) & 0x800) != 0) {
                    posZ = DAT_00e2b1a4;
                }

                // Compute forces
                float forceX = DAT_01218dd4 * boneHeight * DAT_00e2cd54;
                float forceY = (DAT_00e44564 - DAT_01218dc0) * boneWidth * DAT_00e2cd54;

                if ((*(uint32_t*)(data + 0x14) & 8) == 0) {
                    forceX *= invW;
                    forceY *= invW;
                }

                *(float*)(this_ + 0x68) = forceX;
                *(float*)(this_ + 100) = forceY; // +0x64

                float mass = *(float*)(data + 0x1c);
                float impulseX = mass * forceX;
                float impulseY = mass * forceY;

                float hitX = (posX + DAT_00e2b1a4) * boneWidth * scale;
                float hitY = (DAT_00e2b1a4 - posY) * boneHeight * scale;

                // Check if hit point is within bone bounds
                if ((0.0f < hitX + impulseY) && (hitX - impulseY < boneWidth) &&
                    (0.0f < hitY + impulseX) && (hitY - impulseX < boneHeight)) {
                    // Compute hit point and normal
                    float normalX = DAT_00e44564 - (hitY - boneHeight * scale);
                    *(float*)(this_ + 0x5c) = DAT_00e44564 - (hitX - boneWidth * scale);
                    *(float*)(this_ + 0x60) = normalX;
                    *(float*)(this_ + 0x54) = hitX;
                    *(float*)(this_ + 0x58) = hitY;

                    float speedScale = lifetime;
                    if ((*(uint8_t*)(data + 0x14) & 0x10) != 0) {
                        speedScale = DAT_00e2b1a4;
                    }
                    *(float*)(this_ + 0x48) = speedScale;

                    FUN_00504ae0(); // Play impact effect

                    data = *(ProjectileData**)(this_ + 0x20);
                    if ((*(uint32_t*)(data + 0x14) & 0x100) != 0) {
                        currentLifetime = *(float*)(this_ + 0x4c) * lifetime;
                    }
                    if ((*(uint32_t*)(data + 0x14) & 0x70000) != 0) {
                        currentLifetime = *(float*)(this_ + 0x50) * currentLifetime;
                    }

                    if (DAT_00e2e780 <= currentLifetime) {
                        *(uint8_t*)(this_ + 0x3d) = 0; // Clear hit flag
                        uint32_t flags = *(uint32_t*)(data + 0x14);
                        if (((flags & 1) == 0) || (*(int32_t*)(this_ + 0x98) == 0)) {
                            *(uint8_t*)(this_ + 0x3c) = 0; // Deactivate
                        } else {
                            float dmgX = forceX;
                            float dmgY = forceY;
                            if ((flags & 0x20) != 0) {
                                dmgX = DAT_00e446c0;
                                dmgY = _DAT_00e44938;
                            }
                            float hitYLocal = hitY;
                            if ((flags & 0x200) != 0) {
                                if (0.0f <= hitY) {
                                    if ((float)(DAT_01218e42 - 1) < hitY) {
                                        hitYLocal = (float)(DAT_01218e42 - 1);
                                    }
                                } else {
                                    hitYLocal = 0.0f;
                                }
                            }
                            FUN_00505ef0(hitYLocal, *(float*)(data + 0x48) * dmgY,
                                         *(float*)(data + 0x48) * dmgX, *(uint32_t*)(data + 0x4c));
                            *(int32_t*)(this_ + 0x40) = *(int32_t*)(this_ + 0x98);
                            *(uint8_t*)(this_ + 0x3c) = 1; // Keep active
                        }

                        if (*(int32_t*)(this_ + 0x24) != 0) {
                            // Store debug draw data
                            *(float*)(this_ + 0x70) = initialDirX;
                            *(float*)(this_ + 0x74) = initialDirY;
                            *(float*)(this_ + 0x78) = initialDirZ;
                            *(float*)(this_ + 0x7c) = currentLifetime;
                            *(float*)(this_ + 0x88) = forceY;
                            *(float*)(this_ + 0x80) = hitX;
                            *(float*)(this_ + 0x84) = hitY;
                            *(float*)(this_ + 0x8c) = forceX;
                        }
                    }
                }
            }
        } else { // Not in game state 7
            if (*(uint8_t*)(this_ + 0x3d) == 0) { // No hit yet
                if (((*(uint8_t*)(data + 0x14) & 1) == 0) || (*(int32_t*)(this_ + 0x98) == 0)) {
                    int32_t pool = FUN_00505c90(DAT_0120550c);
                    *(int32_t*)(pool + 8) = 0; // Reset some field
                } else {
                    FUN_00504400(*(int32_t*)(this_ + 0x98)); // Remove target entity?
                }

                int32_t debugData = *(int32_t*)(this_ + 0x24);
                if (debugData != 0) {
                    FUN_00504980(); // Update transform

                    // Perform matrix multiplication for position update (different matrix)
                    float vx = *(float*)(this_ + 0x80); // velocityX
                    float vy = *(float*)(this_ + 0x84); // velocityY
                    float vz = *(float*)(this_ + 0x88); // velocityZ
                    float vw = *(float*)(this_ + 0x44); // unknown

                    float newX = vx * DAT_01218e10 + vy * DAT_01218e00 + vz * DAT_01218e20 + vw * DAT_01218e30;
                    float newY = vx * fRam01218e14 + vy * fRam01218e04 + vz * fRam01218e24 + vw * fRam01218e34;
                    float newZ = vx * fRam01218e18 + vy * fRam01218e08 + vz * fRam01218e28 + vw * fRam01218e38;
                    float newW = vx * fRam01218e1c + vy * fRam01218e0c + vz * fRam01218e2c + vw * fRam01218e3c;

                    FUN_005071d0(this_ + 0x70, *(float*)(this_ + 0x80), *(float*)(this_ + 0x84),
                                 newZ, newW, *(float*)(this_ + 0x44),
                                 *(float*)(this_ + 0x88), *(float*)(this_ + 0x8c), debugData,
                                 (*(uint32_t*)(*(int32_t*)(this_ + 0x20) + 0x14) >> 7) & 0xFFFFFF01);
                }
                return 1;
            }
        }
    }
    return 0;
}
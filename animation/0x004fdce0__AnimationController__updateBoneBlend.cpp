// FUNC_NAME: AnimationController::updateBoneBlend
// Address: 0x004FDCE0
// Updates blending for a single bone node, advancing timers and interpolating transforms.

struct BoneNode;
struct Skeleton;

class AnimationController {
public:
    // +0x6C: current blend timer (seconds remaining)
    float blendTimer;
    // +0x70: overshoot timer (clamped to zero)
    float overshootTimer;
    // +0x74: cooldown timer (time until next blend phase)
    float cooldownTimer;
    // +0x78: flags (bit0 = active)
    byte flags;
    // +0x7C: secondary bone node (or null)
    BoneNode* secondaryBone;

    void updateBoneBlend(BoneNode* bone, float deltaTime);
};

struct BoneNode {
    // +0x10: index into skeleton's global transform array
    int boneIndex;
    // +0x28: skeleton that owns this bone
    Skeleton* skeleton;
    // +0x38: blend step counter
    int blendCounter;
    // +0x40-0x4C: local offset/velocity (4 floats)
    float localOffsetX;
    float localOffsetY;
    float localOffsetZ;
    float localOffsetW; // scale or unused
    // +0x50-0x5C: target blend position (4 floats)
    float targetOffsetX;
    float targetOffsetY;
    float targetOffsetZ;
    float targetOffsetW;
};

struct Skeleton {
    // +0x24: flags (bit0 = use local space vs world space)
    byte flags;
};

// External constants and helpers
extern float DAT_00e3ac58;          // epsilon (likely 0.0f)
extern float DAT_00e2cd54;          // blend random constant 1
extern float DAT_00e2b1a4;          // blend random constant 2

// Helper: returns pointer to global bone transform array (4 floats per entry)
inline float* getGlobalBoneTransform(int index) {
    // Accessed via FS:[0x2C] thread-local storage in original assembly
    // Simplified: assume a global array g_boneTransforms
    extern float g_boneTransforms[];
    return &g_boneTransforms[index * 4];
}

// Forward declarations for callees
void AnimationController::onBlendTimerEnd(); // FUN_004fd2c0
float randomFloat();                          // FUN_004e41b0 (returns float in [0,1])
void BoneNode::applyBlendResult(const float blendResult[4]); // FUN_004fd350

void AnimationController::updateBoneBlend(BoneNode* bone, float deltaTime) {
    // Check if blending is active (bit0 of flags)
    if (!(flags & 1)) return;

    // Decrease blend timer
    float newBlendTimer = blendTimer - bone->localOffsetY * deltaTime; // bone->localOffsetY as blend rate? offset+0x44
    blendTimer = newBlendTimer;
    if (newBlendTimer <= 0.0f) {
        bone->blendCounter--;
        onBlendTimerEnd();
    }

    // Update overshoot timer (clamp to epsilon)
    if (DAT_00e3ac58 < overshootTimer) {
        float newOvershoot = overshootTimer - bone->localOffsetX * deltaTime; // bone->localOffsetX as rate? offset+0x40
        if (newOvershoot <= DAT_00e3ac58) {
            newOvershoot = DAT_00e3ac58;
        }
        overshootTimer = newOvershoot;
    }

    // Decrease cooldown timer, reset when ≤ 0
    cooldownTimer -= deltaTime;
    if (cooldownTimer <= 0.0f) {
        float rate = *(float*)(bone->skeleton + 0x90) * DAT_00e2cd54; // possibly skeleton's bone speed
        float fVal = rate;
        randomFloat();
        float newCooldown = (fVal + DAT_00e2b1a4) * rate;
        cooldownTimer = newCooldown;
        randomFloat();
        overshootTimer = newCooldown * DAT_00e2cd54 + DAT_00e2cd54;
    }

    // Determine base transform (local or world)
    float basePos[4];
    bool useLocal = (bone->skeleton->flags & 1) == 0;

    if (useLocal) {
        basePos[0] = bone->localOffsetX;
        basePos[1] = bone->localOffsetY;
        basePos[2] = bone->localOffsetZ;
        basePos[3] = bone->localOffsetW;
    } else {
        float* globalTransform = getGlobalBoneTransform(bone->boneIndex);
        basePos[0] = bone->localOffsetX + globalTransform[0];
        basePos[1] = bone->localOffsetY + globalTransform[1];
        basePos[2] = bone->localOffsetZ + globalTransform[2];
        basePos[3] = globalTransform[3]; // keep w
    }

    // Determine target transform (secondary bone or default)
    float targetPos[4];
    if (secondaryBone == nullptr || (secondaryBone->skeleton->flags & 1) == 0) {
        targetPos[0] = bone->targetOffsetX;
        targetPos[1] = bone->targetOffsetY;
        targetPos[2] = bone->targetOffsetZ;
        targetPos[3] = bone->targetOffsetW;
        if (useLocal) {
            return; // no blending needed if both are local?
        }
    } else {
        float* secondaryGlobal = getGlobalBoneTransform(secondaryBone->boneIndex);
        targetPos[0] = bone->targetOffsetX + secondaryGlobal[0];
        targetPos[1] = bone->targetOffsetY + secondaryGlobal[1];
        targetPos[2] = bone->targetOffsetZ + secondaryGlobal[2];
        targetPos[3] = secondaryGlobal[3];
    }

    // Apply the blend result (probably interpolates between base and target)
    BoneNode::applyBlendResult(targetPos);
}
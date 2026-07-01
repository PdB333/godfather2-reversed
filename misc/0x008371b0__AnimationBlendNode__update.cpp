// FUNC_NAME: AnimationBlendNode::update
// Address: 0x008371b0

// Comments: Updates the blend state of an animation blend node with delta time.
// Handles blend-in/out based on current time and duration, input-driven blend-out activation,
// and integrates with player transform for additive blending.

#include <cstdint>

extern float DAT_00e445ac; // blend out duration constant
extern float DAT_00e44564; // identity value (1.0f) for negation
extern void* DAT_012233a0; // pointer to input device manager singleton

// Forward declarations of helper functions
bool FUN_004709e0(); // isInputAllowed?
void FUN_004df590(); // pauseBlend
void FUN_004df600(); // resumeBlend
void FUN_0045c400(float* target, float* param2, int param3); // setBlendThreshold
void FUN_00836700(float weight); // setBlendWeightFromMenu
void FUN_004df890(float weight); // setBlendWeight
void FUN_008370e0(); // computeBlendInFactor
void FUN_008366c0(float factor); // addBlendInFactor
void* FUN_004262f0(int); // getPlayerTransform (returns pointer to matrix)
void FUN_0056afa0(float* vec); // normalizeVector3
void FUN_0044b4e0(float* dest, float* src); // copyTransformToMatrix
void FUN_004df720(float* matrix); // applyBlendMatrix

class AnimationBlendNode {
public:
    // +0x00: vtable pointer (not shown)
    uint16_t flags;           // +0x84
    float blendWeight;        // +0x88
    float blendWeightX;       // +0x8c
    float blendWeightY;       // +0x90
    float blendWeightZ;       // +0x94
    float blendInThreshold;   // +0xac
    float maxDuration;        // +0xb0
    float currentTime;        // +0xb4
    int32_t flagD8;           // +0xd8 (unknown use)
    int32_t flagDC;           // +0xdc (isLooping? isFinished?)

    int update(float deltaTime);
};

int AnimationBlendNode::update(float deltaTime) {
    float fVar1, fVar2, fVar9, fVar10, fVar11;
    uint32_t uVar6;
    float local_c8;
    float local_c4 = 0.0f;
    float local_c0, local_bc, local_b8, local_b0, local_ac, local_a8;
    float local_70, local_6c, local_68, local_60, local_5c, local_58;
    float local_90, local_8c, local_88, local_80, local_7c, local_78;
    float local_b4; // dummy for matrix copy
    float local_a4, local_94, local_84; // dummies
    float local_b0_vec[3]; // temporary vector
    float local_a0_vec[3];
    float local_9c_vec[3];
    float local_98_vec[3];
    float local_50[19]; // 76 bytes, should be 19 floats (4x4 matrix + extra?)

    // Advance time
    currentTime += deltaTime;

    // Check if input-driven blend-out should be active
    if (!(flags & (1 << 3))) { // bit3 is 0
        // Query input device
        uVar6 = 0;
        if (*(int**)**(int**)(DAT_012233a0 + 4) != nullptr) {
            int* piVar5 = (int*)(**(int**)(DAT_012233a0 + 4))->vtable[0xc](); // getInputDevice()
            if (piVar5 != nullptr) {
                float temp = 0.0f;
                char result = piVar5->vtable[0x10](0x383225a1, &temp); // isButtonDown()
                if (result != 0) {
                    uVar6 = (uint32_t)temp;
                }
            }
        }
        if (uVar6 != 0 && FUN_004709e0() != 0) {
            flags |= 0x10; // set bit4 (blend-out active)
        } else {
            flags &= ~0x10; // clear bit4
        }
    } else {
        flags |= 0x10; // bit3 already set, force blend-out active
    }

    // Blend weight calculation based on time
    local_c8 = blendWeight; // current weight from field
    if (currentTime <= maxDuration) {
        if (blendInThreshold <= currentTime) {
            fVar9 = maxDuration - currentTime;
            if (fVar9 <= blendInThreshold) {
                // blend out phase
                local_c8 = (fVar9 / blendInThreshold) * local_c8;
                if (flags & (1 << 2)) {
                    FUN_0045c400(&DAT_0112dbc4, &blendInThreshold, 0);
                }
                FUN_00836700(blendInThreshold);
            }
        } else {
            // blend in phase
            local_c8 = (currentTime / blendInThreshold) * local_c8;
        }

        // Clamp blend weight to [0, original blendWeight]
        float* pfVar7;
        if ((local_c8 < blendWeight || local_c8 == blendWeight) && (0.0f <= local_c8)) {
            pfVar7 = &local_c8;
        } else {
            pfVar7 = &local_c4; // local_c4 is 0.0f
        }
        local_c8 = *pfVar7;
        FUN_004df890(local_c8); // apply blend weight

        // Handle blend-in/out states
        bool blendOutActive = (flags >> 4) & 1;
        if (blendOutActive == false) {
            if (flagDC == 0) {
                // neither blend-out nor looping: adjust blend-in factor
                FUN_008370e0();
                fVar9 = DAT_00e445ac;
                if (currentTime < blendInThreshold) {
                    fVar9 = blendInThreshold - currentTime;
                }
                FUN_008366c0(fVar9);
            }
        } else {
            if (flagDC != 0) {
                // both blend-out active and looping: pause/resume blend
                FUN_004df590();
                FUN_004df600();
                local_c4 = maxDuration - currentTime;
                if (DAT_00e445ac <= local_c4) {
                    FUN_00836700(DAT_00e445ac);
                } else {
                    FUN_00836700(local_c4);
                }
            }
        }

        // Get player transform matrix
        int* playerTransform = (int*)FUN_004262f0(0);
        float* matrix = (float*)playerTransform;

        // Extract rotation/translation components (three vectors)
        local_c0 = matrix[0x40/4];   // probably translation X
        local_bc = matrix[0x44/4];   // translation Y
        local_b8 = matrix[0x48/4];   // translation Z
        local_a0 = matrix[0x50/4];   // first rotation axis X
        local_9c = matrix[0x54/4];   // first rotation axis Y
        local_98 = matrix[0x58/4];   // first rotation axis Z
        local_90 = matrix[0x60/4];   // second rotation axis X
        local_8c = matrix[0x64/4];   // second rotation axis Y
        local_88 = matrix[0x68/4];   // second rotation axis Z
        local_80 = matrix[0x70/4];   // third rotation axis X? or translation?
        local_7c = matrix[0x74/4];   // third rotation axis Y?
        local_78 = matrix[0x78/4];   // third rotation axis Z?
        // Note: local_b4 is unused; local_74 is from a global; skip for simplicity

        // Normalize the extracted vectors
        float vec1[3] = {local_c0, local_bc, local_b8};
        FUN_0056afa0(vec1);
        local_b0 = vec1[0]; local_ac = vec1[1]; local_a8 = vec1[2];

        float vec2[3] = {local_a0, local_9c, local_98};
        FUN_0056afa0(vec2);
        local_70 = vec2[0]; local_6c = vec2[1]; local_68 = vec2[2];

        float vec3[3] = {local_90, local_8c, local_88};
        FUN_0056afa0(vec3);
        local_60 = vec3[0]; local_5c = vec3[1]; local_58 = vec3[2];

        // Apply blend weights to create offset
        fVar9 = blendWeightX;
        fVar1 = blendWeightY;
        fVar2 = blendWeightZ;

        // Accumulate scaled vectors into local_78, local_80, local_7c
        // These are likely the final additive offset
        local_78 += fVar9 * local_b8 + fVar1 * local_68 + fVar2 * local_58;
        local_80 += fVar9 * local_c0 + fVar1 * local_70 + fVar2 * local_60;
        local_7c += fVar9 * local_bc + fVar1 * local_6c + fVar2 * local_5c;

        // Invert vectors for matrix building (since DAT_00e44564 is likely 0.0f? Actually it's used as subtraction target)
        float invVec1[3] = {DAT_00e44564 - local_b0, DAT_00e44564 - local_ac, DAT_00e44564 - local_a8};
        float invVec2[3] = {DAT_00e44564 - local_90, DAT_00e44564 - local_8c, DAT_00e44564 - local_88};
        // Wait, the original code also negates local_b0, etc. but does not use for matrix? Let's re-check.
        // Actually the subtraction is applied to local_b0, local_ac, etc. then passed to FUN_0044b4e0.
        // The code did: local_b0 = DAT_00e44564 - local_b0; etc. Then copied to local_b0_vec array.
        // So we do the same.

        local_b0 = DAT_00e44564 - local_b0;
        local_ac = DAT_00e44564 - local_ac;
        local_a8 = DAT_00e44564 - local_a8;
        local_90 = DAT_00e44564 - local_90;
        local_8c = DAT_00e44564 - local_8c;
        local_88 = DAT_00e44564 - local_88;

        // Build matrix for blend application
        float matrixData[12] = {
            local_b0, local_ac, local_a8, 0.0f,
            local_90, local_8c, local_88, 0.0f,
            local_80, local_7c, local_78, 0.0f
        };
        FUN_0044b4e0(local_50, matrixData);
        FUN_004df720(local_50);

        if (flagDC != 0) {
            FUN_004df720(local_50);
            FUN_004df890(local_c8);
        }
        return 0; // still active
    } else {
        // Time exceeded maxDuration: finish blend
        if (flagD8 != 0) {
            FUN_004df590();
            FUN_004df600();
        }
        if (flagDC != 0) {
            FUN_004df590();
            FUN_004df600();
        }
        maxDuration = 0.0f;
        flags &= ~1; // clear bit0 (finished flag)
        return 1; // done
    }
}
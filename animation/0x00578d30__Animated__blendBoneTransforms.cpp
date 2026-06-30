// FUNC_NAME: Animated::blendBoneTransforms
// Address: 0x00578d30
// This function blends bone transforms from a circular buffer of animation keyframe data,
// accumulating weighted quaternion-based offsets into an output transform structure.

#include <math.h> // For sin/cos? Not used directly, but inferred.

// Forward declarations (from elsewhere in the codebase)
struct TransformQuat {
    Vector3 position; // +0x00
    float w;          // +0x0C (quaternion w or scale)
};

// Known functions (from other decompilations)
int __thiscall Animated::getNumActiveBones(int this); // FUN_00579170
uint __thiscall Animated::getBlendFlags(int this);   // FUN_00571070
void __thiscall Animated::getBoneTransform(int this, int boneIndex, TransformQuat *out); // FUN_00581d70
void __thiscall Animated::applyBoneOffset(int this, int boneIndex, float weight, TransformQuat *accumulator); // FUN_005781f0
void __thiscall Animated::blendTransforms(TransformQuat *accumulator, const TransformQuat *add, TransformQuat *result); // FUN_0056cba0

int __thiscall FUN_00578d30(int this, int output) {
    int iVar1;
    uint uVar2;
    int iVar3;
    float fVar7;
    float fVar8;
    float local_b4;
    int local_b0;
    int *local_ac;
    float local_a4;
    int local_a0;
    float local_9c;
    float local_98;
    float local_90;
    float local_8c;
    float local_88;
    float local_84;
    float local_80;
    float fStack_7c;
    float fStack_78;
    float fStack_74;
    int *local_6c;
    uint local_68;
    int local_64;
    int local_60;
    float local_5c;
    float local_58;
    float local_50;
    float local_4c;
    float local_48;
    float local_44;
    float local_40;
    float local_3c;
    float local_38;
    float local_34;
    float fStack_30;
    float fStack_2c;
    float fStack_28;
    float fStack_24;
    float fStack_20;
    float fStack_1c;
    float fStack_18;
    float fStack_14;

    local_64 = this;
    int activeBones = Animated::getNumActiveBones(this); // FUN_00579170
    fVar8 = DAT_00e2b1a4; // identity quaternion w = 1.0f

    // Check if animation processing is disabled (flag bit 0x14)
    if (((*(uint *)(this + 0x10) >> 0x14 & 1) == 0) && (activeBones != 0)) {
        fVar7 = 0.0f;
        int *outputTransforms = (int *)(output + 0x10); // Pointer to output transform array (circular buffer)
        *(uint *)(output + 0x18) = 0; // Reset accumulator
        *(uint *)(output + 0x14) = 0;
        *(uint *)outputTransforms = 0;
        *(float *)(output + 0x1c) = fVar8;
        *(uint *)(output + 0x28) = 0;
        *(uint *)(output + 0x24) = 0;
        *(uint *)(output + 0x20) = 0;
        *(float *)(output + 0x2c) = fVar8;
        local_b4 = 0.0f;
        local_68 = Animated::getBlendFlags(this); // FUN_00571070
        local_ac = 0; // current bone pointer
        local_b0 = 0; // bone index counter

        if (activeBones >= 0) {
            do {
                // Compute pointer into circular bone data buffer at this+0x2e4, size 0xE0 per bone
                int boneDataBase = *(int *)(this + 0x2e4);
                int ringBufferMask = *(int *)(this + 0x2e8); // might be buffer size - 1 or wrap offset
                int ringBufferOffset = *(int *)(this + 0x2ec); // base address of bone data array
                int index = ((boneDataBase - activeBones) + local_b0 + 1 + ringBufferMask) % boneDataBase;
                int *boneData = (int *)(index * 0xE0 + ringBufferOffset);
                local_6c = boneData;

                if (local_ac != 0) {
                    local_b4 = (float)local_ac[0x1f] - (float)local_ac[0x1e]; // duration/weight difference
                    local_9c = *(float *)(this + 0x1c); // current time?
                    local_98 = *(float *)(this + 0x24) - fVar8; // end time? minus identity w
                    local_a4 = fVar7;
                    local_a0 = this;
                    local_90 = fVar7;
                    local_8c = fVar7;
                    local_88 = fVar7;
                    local_84 = fVar8;
                    local_80 = fVar7;
                    fStack_7c = fVar7;
                    fStack_78 = fVar7;
                    fStack_74 = fVar8;

                    // Check if bone animation is not null (char at boneData[0x1c] offset 0x70)
                    if ((char)local_ac[0x1c] != '\0') {
                        double dVar6 = (double)(((float)local_ac[0x1e] / (float)local_ac[0x1f]) * 
                                                DAT_00e2afac - DAT_00e2a850);
                        // Possibly sin/cos or interpolation function
                        FUN_00b99fcb(); // unknown helper
                        fVar7 = 0.0f;
                        fVar8 = DAT_00e2b1a4;
                        local_a4 = ((float)dVar6 + DAT_00e2b1a4) * DAT_00e2cd54; // final weight/scalar
                    }

                    uVar2 = local_68;
                    if (local_ac[0x20] == 2) { // bone animation type flag (blend mode?)
                        uVar2 = local_68 | 0x100;
                    }

                    if ((uVar2 & 0x100) == 0) {
                        // Normal blend: get transform at current time
                        local_9c = (float)local_ac[7]; // start time?
                        local_98 = (float)local_ac[7] + local_b4; // end time?
                        (**(code **)(*local_ac + 0x10))(&local_a0); // virtual call: get transform?
                        fVar7 = 0.0f;
                        fVar8 = DAT_00e2b1a4;
                    }

                    local_60 = this;
                    local_50 = fVar7;
                    local_4c = fVar7;
                    local_48 = fVar7;
                    local_44 = fVar8;
                    local_40 = fVar7;
                    local_3c = fVar7;
                    local_38 = fVar7;
                    local_34 = fVar8;

                    if (local_b0 == activeBones) {
                        local_5c = *(float *)(this + 0x1c); // current animation time?
                        local_58 = local_5c + local_b4;
                        Animated::getBoneTransform(this, &local_60); // FUN_00581d70 -> might be this + bone index?
                    } else {
                        local_5c = (float)boneData[7]; // start time for this bone
                        local_58 = (float)boneData[7] + local_b4; // end time
                        (**(code **)(*boneData + 0x10))(); // virtual call on bone data
                    }

                    fStack_28 = 0.0f;
                    fStack_2c = 0.0f;
                    fStack_30 = 0.0f;
                    fStack_24 = DAT_00e2b1a4;
                    fStack_18 = 0.0f;
                    fStack_1c = 0.0f;
                    fStack_20 = 0.0f;
                    fStack_14 = DAT_00e2b1a4;

                    if ((uVar2 & 0x100) == 0) {
                        // Apply the offset (weight * transform) into accumulator
                        Animated::applyBoneOffset(this, local_a4); // FUN_005781f0 -> passes fStack_30 and weight
                        this = local_64;
                        boneData = local_6c;
                    } else {
                        // Blend mode: just copy the base transform
                        fStack_30 = local_50;
                        fStack_2c = local_4c;
                        fStack_28 = local_48;
                        fStack_24 = local_44;
                        fStack_20 = local_40;
                        fStack_1c = local_3c;
                        fStack_18 = local_38;
                        fStack_14 = local_34;
                    }

                    fVar7 = 0.0f;
                    fVar8 = DAT_00e2b1a4;
                    // Accumulate transform into output
                    Animated::blendTransforms((TransformQuat *)outputTransforms, 
                                              (const TransformQuat *)&fStack_30, 
                                              (TransformQuat *)outputTransforms);
                    *(float *)(output + 0x20) = *(float *)(output + 0x20) + fStack_20;
                    *(float *)(output + 0x24) = *(float *)(output + 0x24) + fStack_1c;
                    *(float *)(output + 0x28) = *(float *)(output + 0x28) + fStack_18;
                    *(float *)(output + 0x2c) = *(float *)(output + 0x2c) + fStack_14;
                    *(float *)(output + 0x2c) = fVar8; // Reset w to identity
                }

                local_b0 = local_b0 + 1;
                local_ac = boneData;
            } while (local_b0 <= activeBones);
        }

        // Finalize: blend the base pose (without bone-specific offset) into output
        local_9c = *(float *)(this + 0x1c) + local_b4;
        local_98 = *(float *)(this + 0x24) - fVar8;
        local_a0 = this;
        local_90 = fVar7;
        local_8c = fVar7;
        local_88 = fVar7;
        local_84 = fVar8;
        local_80 = fVar7;
        fStack_7c = fVar7;
        fStack_78 = fVar7;
        fStack_74 = fVar8;
        Animated::getBoneTransform(this, &local_a0); // FUN_00581d70
        Animated::blendTransforms((TransformQuat *)outputTransforms, 
                                  (const TransformQuat *)&local_90, 
                                  (TransformQuat *)outputTransforms);
        *(float *)(output + 0x20) = *(float *)(output + 0x20) + local_80;
        *(float *)(output + 0x24) = *(float *)(output + 0x24) + fStack_7c;
        *(float *)(output + 0x28) = *(float *)(output + 0x28) + fStack_78;
        *(float *)(output + 0x2c) = *(float *)(output + 0x2c) + fStack_74;
        *(float *)(output + 0x2c) = DAT_00e2b1a4;
        return 1; // success
    }

    // If disabled or no bones, just copy base transform
    iVar3 = Animated::getBoneTransform(output); // FUN_00581d70 directly on output
    return iVar3;
}
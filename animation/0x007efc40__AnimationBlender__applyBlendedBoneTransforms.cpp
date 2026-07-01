// FUNC_NAME: AnimationBlender::applyBlendedBoneTransforms
void __thiscall AnimationBlender::applyBlendedBoneTransforms(
    int this,
    float* outBone0,   // +0x10: X; +0x14: Y; +0x18: Z
    float* outBone1,
    float* outBone2,
    float* outBone3,
    float* outBone4,
    float* outBone5,
    float* outBone6,
    float* outBone7,
    undefined4 param10,
    AnimationPoseData* poseData   // source blend data structure
)
{
    float scaleX, scaleY, scaleZ;
    float fVar1, fVar2, fVar3;
    float fVar4 = DAT_00e44564;  // global default position (likely Z offset)
    double blendFactor;

    // Check if animation flags are set (0x5E0 and 0x5E2 likely boolean flags on the controller)
    if (*(byte*)(this + 0x5E2) != 0 || *(byte*)(this + 0x5E0) != 0) {
        fVar1 = *(float*)(poseData + 0x118); // scale factors per axis
        fVar2 = *(float*)(poseData + 0x11C);
        fVar3 = *(float*)(poseData + 0x120);

        // Bone 0: scale poseData's bone transforms by fVar1/fVar2/fVar3
        outBone0[0x10/4] = *(float*)(poseData + 0x170) * fVar1;  // X
        outBone0[0x14/4] = *(float*)(poseData + 0x174) * fVar2;  // Y
        outBone0[0x18/4] = *(float*)(poseData + 0x178) * fVar3;  // Z

        // Bone 1
        outBone1[0x10/4] = *(float*)(poseData + 0x17C) * fVar1;
        outBone1[0x14/4] = *(float*)(poseData + 0x180) * fVar2;
        outBone1[0x18/4] = *(float*)(poseData + 0x184) * fVar3;

        // Bone 2: special case for X – using fVar4 minus scaled value (mirror/flip)
        outBone2[0x10/4] = fVar4 - *(float*)(poseData + 0x188) * fVar1;
        outBone2[0x14/4] = *(float*)(poseData + 0x18C) * fVar2;
        outBone2[0x18/4] = *(float*)(poseData + 400) * fVar3;   // offset 0x190

        // Bone 3
        outBone3[0x10/4] = *(float*)(poseData + 0x194) * fVar1;
        outBone3[0x14/4] = *(float*)(poseData + 0x198) * fVar2;
        outBone3[0x18/4] = *(float*)(poseData + 0x19C) * fVar3;

        // Bone 4
        outBone4[0x10/4] = *(float*)(poseData + 0x1A0) * fVar1;
        outBone4[0x14/4] = *(float*)(poseData + 0x1A4) * fVar2;
        outBone4[0x18/4] = *(float*)(poseData + 0x1A8) * fVar3;

        // Bone 5
        outBone5[0x10/4] = *(float*)(poseData + 0x1AC) * fVar1;
        outBone5[0x14/4] = *(float*)(poseData + 0x1B0) * fVar2;
        outBone5[0x18/4] = *(float*)(poseData + 0x1B4) * fVar3;

        // Bone 6
        outBone6[0x10/4] = *(float*)(poseData + 0x1B8) * fVar1;
        outBone6[0x14/4] = *(float*)(poseData + 0x1BC) * fVar2;
        outBone6[0x18/4] = *(float*)(poseData + 0x1C0) * fVar3;

        // Bone 7
        outBone7[0x10/4] = *(float*)(poseData + 0x1C4) * fVar1;
        outBone7[0x14/4] = *(float*)(poseData + 0x1C8) * fVar2;
        outBone7[0x18/4] = *(float*)(poseData + 0x1CC) * fVar3;

        // Compute blend factor from global state
        blendFactor = (double)FUN_007f3200(DAT_01205228);

        // Apply animation blend to the engine (time-based interpolation)
        FUN_0056d370(
            0,   // unused parameter (0)
            *(float*)(poseData + 0x110) * DAT_00d7007c -
                (*(float*)(poseData + 0x110) - *(float*)(poseData + 0x114)) *
                DAT_00d7007c * (float)blendFactor,
            0,   // unused parameter (0)
            param10
        );
    }
}
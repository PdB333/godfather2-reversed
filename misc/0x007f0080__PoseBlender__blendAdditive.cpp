// FUNC_NAME: PoseBlender::blendAdditive
void __thiscall PoseBlender::blendAdditive(int thisPtr, int outPosePtr, char blendFullBody)
{
    float* boneTransform;
    float blendWeight;
    char flag0;
    char flag2;
    bool doBlend;
    float scaleX, scaleY, scaleZ, scaleW;
    undefined4 result[4];

    flag2 = *(char*)(thisPtr + 0x5e2); // +0x5e2: blendFlag2
    flag0 = *(char*)(thisPtr + 0x5e0); // +0x5e0: blendFlag0
    doBlend = (flag2 != '\0') || (flag0 != '\0'); // if either flag set, enable blending

    if (doBlend) {
        blendWeight = *(float*)(outPosePtr + 0xfe0); // weight for blending
        // Scale the first bone's transform (at this+0x100) by blendWeight
        boneTransform = (float*)(thisPtr + 0x100); // +0x100: bone0 transform (quaternion/vector)
        *boneTransform *= blendWeight;
        *(boneTransform+1) *= blendWeight;
        *(boneTransform+2) *= blendWeight;
        *(boneTransform+3) *= blendWeight;

        // Transform bone0 world matrix with the scaled bone transform
        FUN_0056cba0(outPosePtr + 0xb20, boneTransform, &result); // transform matrix at +0xb20
        *(undefined4*)(outPosePtr + 0xb20) = result[0];
        *(undefined4*)(outPosePtr + 0xb24) = result[1];
        *(undefined4*)(outPosePtr + 0xb28) = result[2];
        *(undefined4*)(outPosePtr + 0xb2c) = result[3];

        // Bone1? (this+0x130)
        FUN_0056cba0(outPosePtr + 0xb50, thisPtr + 0x130, &result);
        *(undefined4*)(outPosePtr + 0xb50) = result[0];
        *(undefined4*)(outPosePtr + 0xb54) = result[1];
        *(undefined4*)(outPosePtr + 0xb58) = result[2];
        *(undefined4*)(outPosePtr + 0xb5c) = result[3];

        // Bone2? (this+0x160)
        FUN_0056cba0(outPosePtr + 0xaf0, thisPtr + 0x160, &result);
        *(undefined4*)(outPosePtr + 0xaf0) = result[0];
        *(undefined4*)(outPosePtr + 0xaf4) = result[1];
        *(undefined4*)(outPosePtr + 0xaf8) = result[2];
        *(undefined4*)(outPosePtr + 0xafc) = result[3];

        // Bone3? (this+0x130? Actually previous is 0x130, maybe bone index offset)
        FUN_0056cba0(outPosePtr + 0xac0, thisPtr + 0x130, &result);
        *(undefined4*)(outPosePtr + 0xac0) = result[0];
        *(undefined4*)(outPosePtr + 0xac4) = result[1];
        *(undefined4*)(outPosePtr + 0xac8) = result[2];
        *(undefined4*)(outPosePtr + 0xacc) = result[3];

        if (blendFullBody != '\0') {
            // Full body blend: update many more bones
            // Bone at this+400 (0x190)
            FUN_0056cba0(outPosePtr + 0xb80, thisPtr + 0x190, &result);
            *(undefined4*)(outPosePtr + 0xb80) = result[0];
            *(undefined4*)(outPosePtr + 0xb84) = result[1];
            *(undefined4*)(outPosePtr + 0xb88) = result[2];
            *(undefined4*)(outPosePtr + 0xb8c) = result[3];

            // Bone at this+0x1c0
            FUN_0056cba0(outPosePtr + 0xbb0, thisPtr + 0x1c0, &result);
            *(undefined4*)(outPosePtr + 0xbb0) = result[0];
            *(undefined4*)(outPosePtr + 0xbb4) = result[1];
            *(undefined4*)(outPosePtr + 0xbb8) = result[2]; // note: +0xbb8 (3000 decimal = 0xbb8)
            *(undefined4*)(outPosePtr + 0xbbc) = result[3];

            // Accumulate positions (translation offsets) for subsequent bones
            // Bone at this+0x200: add to outPose+0xbf0
            *(float*)(outPosePtr + 0xbf0) += *(float*)(thisPtr + 0x200);
            *(float*)(outPosePtr + 0xbf4) += *(float*)(thisPtr + 0x204);
            *(float*)(outPosePtr + 0xbf8) += *(float*)(thisPtr + 0x208);
            *(float*)(outPosePtr + 0xbfc) += *(float*)(thisPtr + 0x20c);

            // Bone at this+0x230
            *(float*)(outPosePtr + 0xc20) += *(float*)(thisPtr + 0x230);
            *(float*)(outPosePtr + 0xc24) += *(float*)(thisPtr + 0x234);
            *(float*)(outPosePtr + 0xc28) += *(float*)(thisPtr + 0x238);
            *(float*)(outPosePtr + 0xc2c) += *(float*)(thisPtr + 0x23c);

            // ... continue pattern for all remaining bones
            // (for brevity, I'll show the structure but the full is repetitive)
            // Bone at this+0x260
            *(float*)(outPosePtr + 0xc50) += *(float*)(thisPtr + 0x260);
            *(float*)(outPosePtr + 0xc54) += *(float*)(thisPtr + 0x264);
            *(float*)(outPosePtr + 0xc58) += *(float*)(thisPtr + 0x268);
            *(float*)(outPosePtr + 0xc5c) += *(float*)(thisPtr + 0x26c);

            // Bone at this+0x290
            *(float*)(outPosePtr + 0xc80) += *(float*)(thisPtr + 0x290);
            *(float*)(outPosePtr + 0xc84) += *(float*)(thisPtr + 0x294);
            *(float*)(outPosePtr + 0xc88) += *(float*)(thisPtr + 0x298);
            *(float*)(outPosePtr + 0xc8c) += *(float*)(thisPtr + 0x29c);

            // Transform bone at this+0x2b0
            FUN_0056cba0(outPosePtr + 0xca0, thisPtr + 0x2b0, &result);
            *(undefined4*)(outPosePtr + 0xca0) = result[0];
            *(undefined4*)(outPosePtr + 0xca4) = result[1];
            *(undefined4*)(outPosePtr + 0xca8) = result[2];
            *(undefined4*)(outPosePtr + 0xcac) = result[3];

            // Bone at this+0x2c0 (accumulate)
            *(float*)(outPosePtr + 0xcb0) += *(float*)(thisPtr + 0x2c0);
            *(float*)(outPosePtr + 0xcb4) += *(float*)(thisPtr + 0x2c4);
            *(float*)(outPosePtr + 0xcb8) += *(float*)(thisPtr + 0x2c8);
            *(float*)(outPosePtr + 0xcbc) += *(float*)(thisPtr + 0x2cc);

            // Transform bone at this+0x2e0
            FUN_0056cba0(outPosePtr + 0xcd0, thisPtr + 0x2e0, &result);
            *(undefined4*)(outPosePtr + 0xcd0) = result[0];
            *(undefined4*)(outPosePtr + 0xcd4) = result[1];
            *(undefined4*)(outPosePtr + 0xcd8) = result[2];
            *(undefined4*)(outPosePtr + 0xcdc) = result[3];

            // Accumulate at this+0x2f0
            *(float*)(outPosePtr + 0xce0) += *(float*)(thisPtr + 0x2f0);
            *(float*)(outPosePtr + 0xce4) += *(float*)(thisPtr + 0x2f4);
            *(float*)(outPosePtr + 0xce8) += *(float*)(thisPtr + 0x2f8);
            *(float*)(outPosePtr + 0xcec) += *(float*)(thisPtr + 0x2fc);

            // Accumulate at this+320 (0x320? Actually 0x324)
            *(float*)(outPosePtr + 0xd10) += *(float*)(thisPtr + 0x320);
            *(float*)(outPosePtr + 0xd14) += *(float*)(thisPtr + 0x324);
            *(float*)(outPosePtr + 0xd18) += *(float*)(thisPtr + 0x328);
            *(float*)(outPosePtr + 0xd1c) += *(float*)(thisPtr + 0x32c);

            // Accumulate at this+0x350
            *(float*)(outPosePtr + 0xd40) += *(float*)(thisPtr + 0x350);
            *(float*)(outPosePtr + 0xd44) += *(float*)(thisPtr + 0x354);
            *(float*)(outPosePtr + 0xd48) += *(float*)(thisPtr + 0x358);
            *(float*)(outPosePtr + 0xd4c) += *(float*)(thisPtr + 0x35c);

            // Accumulate at this+0x380
            *(float*)(outPosePtr + 0xd70) += *(float*)(thisPtr + 0x380);
            *(float*)(outPosePtr + 0xd74) += *(float*)(thisPtr + 0x384);
            *(float*)(outPosePtr + 0xd78) += *(float*)(thisPtr + 0x388);
            *(float*)(outPosePtr + 0xd7c) += *(float*)(thisPtr + 0x38c);

            // Accumulate at this+0x3b0
            *(float*)(outPosePtr + 0xda0) += *(float*)(thisPtr + 0x3b0);
            *(float*)(outPosePtr + 0xda4) += *(float*)(thisPtr + 0x3b4);
            *(float*)(outPosePtr + 0xda8) += *(float*)(thisPtr + 0x3b8);
            *(float*)(outPosePtr + 0xdac) += *(float*)(thisPtr + 0x3bc);

            // Accumulate at this+0x3e0
            *(float*)(outPosePtr + 0xdd0) += *(float*)(thisPtr + 0x3e0);
            *(float*)(outPosePtr + 0xdd4) += *(float*)(thisPtr + 0x3e4);
            *(float*)(outPosePtr + 0xdd8) += *(float*)(thisPtr + 0x3e8);
            *(float*)(outPosePtr + 0xddc) += *(float*)(thisPtr + 0x3ec);

            // Accumulate at this+0x410
            *(float*)(outPosePtr + 0xe00) += *(float*)(thisPtr + 0x410);
            *(float*)(outPosePtr + 0xe04) += *(float*)(thisPtr + 0x414);
            *(float*)(outPosePtr + 0xe08) += *(float*)(thisPtr + 0x418);
            *(float*)(outPosePtr + 0xe0c) += *(float*)(thisPtr + 0x41c);

            // Accumulate at this+0x440
            *(float*)(outPosePtr + 0xe30) += *(float*)(thisPtr + 0x440);
            *(float*)(outPosePtr + 0xe34) += *(float*)(thisPtr + 0x444);
            *(float*)(outPosePtr + 0xe38) += *(float*)(thisPtr + 0x448);
            *(float*)(outPosePtr + 0xe3c) += *(float*)(thisPtr + 0x44c);

            // Accumulate at this+0x470
            *(float*)(outPosePtr + 0xe60) += *(float*)(thisPtr + 0x470);
            *(float*)(outPosePtr + 0xe64) += *(float*)(thisPtr + 0x474);
            *(float*)(outPosePtr + 0xe68) += *(float*)(thisPtr + 0x478);
            *(float*)(outPosePtr + 0xe6c) += *(float*)(thisPtr + 0x47c);

            // Accumulate at this+0x4a0
            *(float*)(outPosePtr + 0xe90) += *(float*)(thisPtr + 0x4a0);
            *(float*)(outPosePtr + 0xe94) += *(float*)(thisPtr + 0x4a4);
            *(float*)(outPosePtr + 0xe98) += *(float*)(thisPtr + 0x4a8);
            *(float*)(outPosePtr + 0xe9c) += *(float*)(thisPtr + 0x4ac);

            // Accumulate at this+0x4d0
            *(float*)(outPosePtr + 0xec0) += *(float*)(thisPtr + 0x4d0);
            *(float*)(outPosePtr + 0xec4) += *(float*)(thisPtr + 0x4d4);
            *(float*)(outPosePtr + 0xec8) += *(float*)(thisPtr + 0x4d8);
            *(float*)(outPosePtr + 0xecc) += *(float*)(thisPtr + 0x4dc);

            // Accumulate at this+0x500
            *(float*)(outPosePtr + 0xef0) += *(float*)(thisPtr + 0x500);
            *(float*)(outPosePtr + 0xef4) += *(float*)(thisPtr + 0x504);
            *(float*)(outPosePtr + 0xef8) += *(float*)(thisPtr + 0x508);
            *(float*)(outPosePtr + 0xefc) += *(float*)(thisPtr + 0x50c);

            // Accumulate at this+0x530
            *(float*)(outPosePtr + 0xf20) += *(float*)(thisPtr + 0x530);
            *(float*)(outPosePtr + 0xf24) += *(float*)(thisPtr + 0x534);
            *(float*)(outPosePtr + 0xf28) += *(float*)(thisPtr + 0x538);
            *(float*)(outPosePtr + 0xf2c) += *(float*)(thisPtr + 0x53c);

            // Accumulate at this+0x560
            *(float*)(outPosePtr + 0xf50) += *(float*)(thisPtr + 0x560);
            *(float*)(outPosePtr + 0xf54) += *(float*)(thisPtr + 0x564);
            *(float*)(outPosePtr + 0xf58) += *(float*)(thisPtr + 0x568);
            *(float*)(outPosePtr + 0xf5c) += *(float*)(thisPtr + 0x56c);

            // Accumulate at this+0x590
            *(float*)(outPosePtr + 0xf80) += *(float*)(thisPtr + 0x590);
            *(float*)(outPosePtr + 0xf84) += *(float*)(thisPtr + 0x594);
            *(float*)(outPosePtr + 0xf88) += *(float*)(thisPtr + 0x598);
            *(float*)(outPosePtr + 0xf8c) += *(float*)(thisPtr + 0x59c);

            // Transform bone at this+0x5b0
            FUN_0056cba0(outPosePtr + 0xfa0, thisPtr + 0x5b0, &result);
            *(undefined4*)(outPosePtr + 0xfa0) = result[0];
            *(undefined4*)(outPosePtr + 0xfa4) = result[1];
            *(undefined4*)(outPosePtr + 0xfa8) = result[2];
            *(undefined4*)(outPosePtr + 0xfac) = result[3];
        }
    }

    // Check if blend flags indicate full convergence
    if ((*(char*)(thisPtr + 0x5e0) == *(char*)(thisPtr + 0x5e1)) &&
        (*(char*)(thisPtr + 0x5e2) == *(char*)(thisPtr + 0x5e3))) {
        FUN_007faeb0(); // Possibly finalize blend
        if (flag2 != '\0') {
            FUN_007f4f20(0); // Reset upper body blend
        }
        if (flag0 != '\0') {
            FUN_007f5000(0); // Reset lower body blend
        }
    }
}
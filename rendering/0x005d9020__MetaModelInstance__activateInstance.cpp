// FUNC_NAME: MetaModelInstance::activateInstance

void MetaModelInstance::activateInstance(int param_1) // param_1 is this pointer, but Ghidra shows __fastcall
{
    // Offset definitions:
    // +0x0a4: m_active (int)
    // +0x010: m_pModel (pointer to something)
    // +0x014: m_pSkeleton (pointer)
    // +0x130: m_bHasAnimData (char)
    // +0x150: m_jointTransforms (presumably array)
    // +0x140: m_bindPoseTransforms
    // +0x168: m_numJointsInBindPose (int)
    // +0x164: m_numJointsInJointTransforms
    // +0x174: m_pSkinDeformer (pointer)
    // +0x16c: m_materialCount (int)
    // +0x160: m_vertexBuffer (pointer)
    // +0x100: m_animFrameIndex (uint)
    // +0x110: m_animLayerIndex (int) * 0xc -> stride
    // +0x0b8: m_boneOffsetArray (int array)

    // Global active instance tracker
    extern int g_ActiveInstance; // DAT_012058e8

    if (g_ActiveInstance == param_1) {
        *(int *)(param_1 + 0xa4) = 0; // deactivate itself
    } else {
        *(int *)(param_1 + 0xa4) = 1; // mark as active
        g_ActiveInstance = param_1;

        // Release previous model and skeleton
        ReleaseModel(*(int *)(param_1 + 0x10));
        ReleaseSkeleton(*(int *)(param_1 + 0x14));
    }

    // If the instance has animation data, update joint transforms and skin
    if (*(char *)(param_1 + 0x130) != '\0') {
        // Apply bone transforms from bind pose to current joint transforms
        ApplyBoneTransforms(*(int *)(param_1 + 0x174),
                            *(int *)(param_1 + 0x168),
                            param_1 + 0x150);
        ApplyBoneTransforms(*(int *)(param_1 + 0x174),
                            *(int *)(param_1 + 0x164),
                            param_1 + 0x140);

        // Update skinned mesh
        UpdateSkinnedMesh(*(int *)(param_1 + 0x174),
                          *(int *)(param_1 + 0x16c),
                          *(int *)(param_1 + 0x160));
    }

    // Compute scaling from current animation frame and apply
    int iVar1 = *(int *)(param_1 + 0xb8 + *(int *)(param_1 + 0x110) * 0xc);
    if (iVar1 != 0) {
        // Pointer to a global animation frame info table (0x38 bytes per entry)
        void* animFrameTableEntry;
        if (*(uint *)(param_1 + 0x100) < 0x1000) {
            animFrameTableEntry = &g_AnimFrameTable + *(uint *)(param_1 + 0x100) * 0x38;
        } else {
            animFrameTableEntry = nullptr;
        }

        float scaleX = g_ScaleConst / (float)*(ushort*)((char*)animFrameTableEntry + 2);
        float scaleY = g_ScaleConst / (float)*(ushort*)((char*)animFrameTableEntry + 4);

        SetScale(*(int *)(param_1 + 0x14), iVar1, &scaleX);
    }

    return;
}
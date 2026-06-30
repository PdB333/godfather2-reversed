// FUNC_NAME: AnimationStateMachine::updateBlendTrees
int __fastcall AnimationStateMachine::updateBlendTrees(AnimationStateMachine* this)
{
    // [0x005388a0] Update animation blending parameters based on current state.
    // Called every frame to drive blend tree interpolation.

    FUN_00612a60(); // Likely enterProfileScope or debug marker

    int extraData = *(int*)(this + 0x10);
    if (extraData == DAT_01219908 && DAT_01219928 != 0)
    {
        Vector4 blendIn; // local_20..local_14
        blendIn.x = 0.0f; blendIn.y = 0.0f; blendIn.z = 0.0f; blendIn.w = 0.0f;
        FUN_0060add0(extraData, DAT_01219928, &blendIn); // Add blend node with zero weights
    }

    int currentState = *(int*)(this + 0x14); // Current animation state ID
    if (currentState == *(int*)(this + 0x470)) // State 0: e.g., Idle
    {
        // Set up blend trees for state 0
        FUN_0060add0(currentState, *(int*)(this + 0x254), this + 0xb0); // target bone blend
        FUN_0060add0(*(int*)(this + 0x14), *(int*)(this + 0x258), this + 0xc0); // blend from state?
        FUN_0060add0(*(int*)(this + 0x14), *(int*)(this + 0x25c), this + 0xd0);

        int boneIndex = *(int*)(this + 0xa4); // bone index or handle
        if (*(int*)(this + 0x260) != 0) // extra bone override?
        {
            boneIndex = FUN_006063b0(); // Get alternative bone
        }

        uint flags = *(uint*)(this + 0x264); // Flags controlling blend behavior
        if (flags == 0)
            return boneIndex;

        uint boneIdx = *(uint*)(this + 0xa4);
        BoneInfo* boneInfo = (boneIdx < 0x1000) ? (&DAT_011a0f28 + boneIdx * 0x38) : NULL;
        if (boneInfo != NULL)
        {
            Vector4 blendWeights;
            blendWeights.z = kAnimationTimeScale / boneInfo->field_2; // scale factor
            // x,y,w set later...
        }
        goto commonBlend;
    }
    else if (currentState == *(int*)(this + 0x474)) // State 1
    {
        FUN_0060add0(currentState, *(int*)(this + 0x26c), this + 0xb0);
        FUN_0060add0(*(int*)(this + 0x14), *(int*)(this + 0x270), this + 0xc0);
        FUN_0060add0(*(int*)(this + 0x14), *(int*)(this + 0x274), this + 0xd0);

        if (*(int*)(this + 0x278) != 0)
            FUN_006063b0(); // Extra processing
        if (*(int*)(this + 0x27c) != 0)
        {
            FUN_0060b2f0(*(int*)(this + 0x14), *(int*)(this + 0x27c), *(int*)(this + 0xe0));
        }
        int val = *(int*)(this + 0x280);
        if (val != 0)
        {
            FUN_0060add0(*(int*)(this + 0x14), val, this + 0x140);
        }
        if (*(int*)(this + 0x284) != 0)
        {
            uint boneIdx = *(uint*)(this + 0xa4);
            Vector4 blendWeights = {0.0f, 0.0f, 0.0f, 0.0f};
            BoneInfo* boneInfo = (boneIdx < 0x1000) ? (&DAT_011a0f28 + boneIdx * 0x38) : NULL;
            if (boneInfo != NULL)
            {
                blendWeights.z = kAnimationTimeScale / boneInfo->field_2;
                boneInfo = (boneIdx < 0x1000) ? (&DAT_011a0f28 + boneIdx * 0x38) : NULL;
                blendWeights.w = kAnimationTimeScale / boneInfo->field_4;
            }
            FUN_0060add0(*(int*)(this + 0x14), *(int*)(this + 0x284), &blendWeights);
        }
        uint flags = *(uint*)(this + 0x288);
        if (flags == 0) return boneIndex; // return whatever boneIndex was (??)
        uint boneIdx2 = *(uint*)(this + 0xe0);
        BoneInfo* boneInfo2 = (boneIdx2 < 0x1000) ? (&DAT_011a0f28 + boneIdx2 * 0x38) : NULL;
        if (boneInfo2 != NULL)
            goto commonBlend;
    }
    else if (currentState == *(int*)(this + 0x478)) // State 2
    {
        FUN_0060add0(currentState, *(int*)(this + 0x29c), this + 0xb0);
        FUN_0060add0(*(int*)(this + 0x14), *(int*)(this + 0x2a0), this + 0xc0);
        FUN_0060b2f0(*(int*)(this + 0x14), *(int*)(this + 0x28c), *(int*)(this + 0xe4));
        FUN_0060b2f0(*(int*)(this + 0x14), *(int*)(this + 0x290), *(int*)(this + 0xe8));
        FUN_0060add0(*(int*)(this + 0x14), *(int*)(this + 0x294), this + 0xf0);
        int val = FUN_0060add0(*(int*)(this + 0x14), *(int*)(this + 0x298), this + 0x100);

        if (*(int*)(this + 0x2a4) != 0)
        {
            Vector4 blendWeights;
            blendWeights.x = 0.0f; blendWeights.y = 0.0f;
            float scale = kAnimationTimeScale;
            BoneInfo* bi = (BoneInfo*)FUN_00606370(*(int*)(this + 0xe4)); // low part of returned longlong
            blendWeights.z = scale / bi->field_2;
            blendWeights.w = scale / bi->field_4;
            FUN_0060add0(*(int*)(this + 0x14), highPartOfPointer, &blendWeights); // Note: high part used incorrectly?
        }
        if (*(int*)(this + 0x268) == 0)
            return val;
        // Further processing...
    }
    else // Fallback: handle based on flags
    {
        uint flags = *(uint*)(this + 0x134); // Flags for advanced blending
        if (flags != 0)
        {
            if (currentState != *(int*)(this + 0x494)) // Not state 9
            {
                // ... complex branch using variationIndex
                int varIndex = *(int*)(this + 0x138); // variation index (0-3 maybe)
                float fVar = kSomeConstant; // depends on flags
                float fVar2 = kSomeOtherConstant;
                // etc.
                BoneInfo* bi = (BoneInfo*)FUN_00606370(*(int*)(this + 0x??)); // unclear
                // Set up blendWeights using bi->field_2 and field_4
                int target = *(int*)(this + 0x2d4 + varIndex * 4);
                if (target != 0) FUN_0060add0(*(int*)(this + 0x14), target, this + 0x110);
                target = *(int*)(this + 0x30c + varIndex * 4);
                if (target != 0) FUN_0060b2f0(*(int*)(this + 0x14), target, *(int*)(this + 0x120));
                target = *(int*)(this + 0x344 + varIndex * 4);
                if (target != 0) FUN_0060b2f0(*(int*)(this + 0x14), target, *(int*)(this + 0x124));
                target = *(int*)(this + 0x3ec + varIndex * 4);
                if (target != 0) { /* more blending */ }
                return FUN_00539aa0(*(int*)(this + 0x130));
            }
            else // State 9
            {
                // ... similar but different offsets
            }
        }
        else // No flags set
        {
            // Check states 0x47c, 0x480, 0x484, 0x488, 0x48c, 0x490
            if (currentState == *(int*)(this + 0x47c)) // State 3
            {
                // Set up another blend tree
                // ...
                return val;
            }
            else if (currentState == *(int*)(this + 0x480) || currentState == *(int*)(this + 0x484) || currentState == *(int*)(this + 0x488))
            {
                // State 4,5,6
                // ...
                return val;
            }
            else if (currentState == *(int*)(this + 0x48c)) // State 7
            {
                // ...
                return val;
            }
            else if (currentState == *(int*)(this + 0x490)) // State 8
            {
                // ...
                return val;
            }
        }
    }

commonBlend:
    // Common blend code reached via goto
    BoneInfo* bi = (BoneInfo*)lowPartOfLonglong; // not defined here
    Vector4 blendWeights;
    blendWeights.x = 0.0f;
    blendWeights.y = 0.0f;
    blendWeights.z = kAnimationTimeScale / bi->field_2;
    blendWeights.w = kAnimationTimeScale / bi->field_4;
    int result = FUN_0060add0(*(int*)(this + 0x14), (int)highPart, &blendWeights);
    return result;
}
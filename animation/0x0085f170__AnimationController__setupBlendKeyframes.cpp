//FUNC_NAME: AnimationController::setupBlendKeyframes
void __thiscall AnimationController::setupBlendKeyframes(int *thisPtr)
{
    // Call virtual function at vtable+0x1b8 to get some time value (e.g., animation time)
    float10 timeValue = (**(code (__thiscall **)(int *))(*(int *)thisPtr + 0x1b8))(thisPtr);
    
    // Add global time offset and clamp to minimum
    float clampedTime = (float)(timeValue + (float10)DAT_00d5d7b8);
    if (clampedTime < (float)DAT_00d7577c) {
        clampedTime = (float)DAT_00d7577c;
    }
    
    // Read bone indices from object members (offsets 0x3f6 and 0x3f7)
    int boneIndex1 = thisPtr[0x3f7]; // +0xFDC
    int boneIndex2 = thisPtr[0x3f6]; // +0xFD8
    
    // Compute blend weight: global max minus clamped time
    float blendWeight = DAT_00e44564 - clampedTime;
    
    // Build an array of 8 keyframe structures (each 12 bytes: flag, boneIndex, weight)
    // The flags alternate between two global constants (likely blend modes or color IDs)
    struct Keyframe {
        uint32_t flag;      // +0x00
        int32_t boneIndex;  // +0x04
        float weight;       // +0x08
    } keyframes[8];
    
    // First keyframe: flag = DAT_00d757bc, bone = boneIndex1, weight = blendWeight
    keyframes[0].flag = DAT_00d757bc;
    keyframes[0].boneIndex = boneIndex1;
    keyframes[0].weight = blendWeight;
    
    // Second keyframe: flag = DAT_00d75780, bone = boneIndex1, weight = blendWeight
    keyframes[1].flag = DAT_00d75780;
    keyframes[1].boneIndex = boneIndex1;
    keyframes[1].weight = blendWeight;
    
    // Third keyframe: flag = DAT_00d757bc, bone = boneIndex2, weight = blendWeight
    keyframes[2].flag = DAT_00d757bc;
    keyframes[2].boneIndex = boneIndex2;
    keyframes[2].weight = blendWeight;
    
    // Fourth keyframe: flag = DAT_00d75780, bone = boneIndex2, weight = blendWeight
    keyframes[3].flag = DAT_00d75780;
    keyframes[3].boneIndex = boneIndex2;
    keyframes[3].weight = blendWeight;
    
    // Fifth keyframe: flag = DAT_00d757bc, bone = boneIndex1, weight = clampedTime
    keyframes[4].flag = DAT_00d757bc;
    keyframes[4].boneIndex = boneIndex1;
    keyframes[4].weight = clampedTime;
    
    // Sixth keyframe: flag = DAT_00d75780, bone = boneIndex1, weight = clampedTime
    keyframes[5].flag = DAT_00d75780;
    keyframes[5].boneIndex = boneIndex1;
    keyframes[5].weight = clampedTime;
    
    // Seventh keyframe: flag = DAT_00d757bc, bone = boneIndex2, weight = clampedTime
    keyframes[6].flag = DAT_00d757bc;
    keyframes[6].boneIndex = boneIndex2;
    keyframes[6].weight = clampedTime;
    
    // Eighth keyframe: flag = DAT_00d75780, bone = boneIndex2, weight = clampedTime
    keyframes[7].flag = DAT_00d75780;
    keyframes[7].boneIndex = boneIndex2;
    keyframes[7].weight = clampedTime;
    
    // Call function to apply these keyframes to the blend data at offset 0x3e5 (0xF94)
    // The last parameter (0xb) might be the number of keyframes or a blend layer index
    FUN_00851440(thisPtr, thisPtr + 0x3e5, &keyframes, 0xb);
}
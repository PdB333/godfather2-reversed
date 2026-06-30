// FUNC_NAME: MetaModelInstance::attachObjectToClosestBone
void __fastcall MetaModelInstance::attachObjectToClosestBone(int this) {
    // Get distances from two candidate bone transforms (offsets +0x1C and +0x28)
    // These likely represent world-space positions or orientations of left/right hand bones
    float distance1 = Math::GetDistanceFromTransform(1, this + 0x1C, 0);  // FUN_008c51a0
    float distance2 = Math::GetDistanceFromOtherTransform(1, this + 0x28, 0, 0, 0); // FUN_008c52f0

    // Compare which bone transform is closer to the target
    bool useFirstBone = Math::IsCloser(distance1, distance2); // FUN_008bd7c0

    if (useFirstBone) {
        int boneIndex = getBoneIndexFromTransform(this + 0x1C); // FUN_006bf050
        if (boneIndex != 0) {
            attachObjectToBone(*(int *)(this + 0x10), boneIndex); // FUN_008c29f0
        }
    } else {
        int boneIndex = getBoneIndexFromTransform(this + 0x28); // FUN_006bf050
        if (boneIndex != 0) {
            attachObjectToAlternateBone(*(int *)(this + 0x10), boneIndex); // FUN_008c2ab0
        }
    }
}
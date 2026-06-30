// FUNC_NAME: Animated::updateBoneTransform
void __thiscall Animated::updateBoneTransform(void *this) {
    int animState;
    int stateId;
    int otherId;
    float scaleX, scaleY, aspectX, aspectY;
    float temp[4];
    BoneInfo *boneInfo;
    unsigned int boneIndex;

    // Some initial system call (e.g., profile scope)
    FUN_00612a60();

    // Read current animation state from offset +0x14
    animState = *(int *)((char *)this + 0x14);

    // Read fallback ID from global
    stateId = DAT_01219920;

    if (animState != DAT_012198f0) {
        // Not the default state
        if (animState != *(int *)((char *)this + 0x108)) {
            if (animState == DAT_012198f8) {
                // State F8: apply extra transform and set new state
                FUN_0060add0(animState, DAT_0121991c, (float *)((char *)this + 0xc0));
                FUN_0060b2f0(*(int *)((char *)this + 0x14), DAT_01219910, *(int *)((char *)this + 0xa4));
                animState = DAT_0121992c;
            }
            else {
                if (animState != DAT_012198fc) {
                    if (animState == *(int *)((char *)this + 0x114)) {
                        FUN_0060b2f0(animState, *(int *)((char *)this + 0xf8), *(int *)((char *)this + 0xa4));
                    }
                    goto skipBranch;
                }
                // State FC
                FUN_0060b2f0(animState, DAT_01219914, *(int *)((char *)this + 0xa4));
                animState = DAT_01219930;
            }

            if (animState != 0) {
                // Read secondary ID from +0x10
                stateId = *(int *)((char *)this + 0x10);
                scaleX = 0.0f;
                scaleY = 0.0f;
                aspectX = 0.0f;
                aspectY = 0.0f;

                // Check for known state pairs
                if ((stateId == DAT_01219908 && (otherId = DAT_01219928, DAT_01219928 != 0)) ||
                    (stateId == DAT_01219900 && (otherId = DAT_01219924, DAT_01219924 != 0))) {
                    FUN_0060add0(stateId, otherId, &scaleX);
                }

                // Use bone index from +0xa4 to access bone info table
                boneIndex = *(unsigned int *)((char *)this + 0xa4);
                if (boneIndex < 0x1000) {
                    boneInfo = (BoneInfo *)((char *)&DAT_011a0f28 + boneIndex * 0x38);
                }
                else {
                    boneInfo = (BoneInfo *)0x0;
                }
                // Compute scale from bone dimensions (inverse of lenX, lenY)
                scaleX = DAT_00e2b1a4 / (float)*(unsigned short *)((char *)boneInfo + 2);
                if (boneIndex < 0x1000) {
                    boneInfo = (BoneInfo *)((char *)&DAT_011a0f28 + boneIndex * 0x38);
                }
                else {
                    boneInfo = (BoneInfo *)0x0;
                }
                scaleY = DAT_00e2b1a4 / (float)*(unsigned short *)((char *)boneInfo + 4);
                // Apply aspect ratio multiplier
                aspectX = scaleX * DAT_00e2cd54;
                aspectY = scaleY * DAT_00e2cd54;

                // Write combined transform
                float combined[4] = { scaleX, scaleY, aspectX, aspectY };
                FUN_0060add0(*(int *)((char *)this + 0x14), animState, combined);
                return;
            }
        }
        else {
            // If animState matches offset +0x108, use value from +0xfc
            stateId = *(int *)((char *)this + 0xfc);
        }
        // Default fallback: apply transform from stateId to offset +0xc0
        FUN_0060add0(animState, stateId, (float *)((char *)this + 0xc0));
    }

skipBranch:
    // Post-processing: if secondary state matches known pairs, apply global transform
    animState = *(int *)((char *)this + 0x10);
    if ((animState == DAT_01219908 && (stateId = DAT_01219928, DAT_01219928 != 0)) ||
        (animState == DAT_01219900 && (stateId = DAT_01219924, DAT_01219924 != 0))) {
        FUN_0060add0(animState, stateId, &DAT_011f6680);
    }
    return;
}
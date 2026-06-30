// FUNC_NAME: Animated::updateBoneBlendWeight
void Animated::updateBoneBlendWeight(BoneTimeInfo* pBoneInfo) {
    float fVar1;
    char localBoneIndex;

    // Check conditions: 
    // - either timer > -1 or time threshold <= global constant
    // - active flag at offset 0xBC is set
    // - boneIndex is negative OR current blend weight <= base blend time
    if ((((*(int*)(this + 0x110) > -1) || (*(float*)(this + 0x114) <= DAT_00e2b05c)) &&
         (*(int*)(this + 0xbc) != 0)) &&
        ((localBoneIndex = *(char*)(pBoneInfo + 10), localBoneIndex < 0) ||
         (fVar1 = *(float*)(this + 0xc0 + localBoneIndex * 4),
          fVar1 <= *(float*)(this + 0x78)))) {
        // If a parent bone index exists
        if (*(char*)(pBoneInfo + 9) >= 0) {
            // Read parent bone's time from an array of 8-byte entries (float at offset 4)
            fVar1 = *(float*)(*(int*)(pBoneInfo + 0xc) + 4 + *(char*)(pBoneInfo + 9) * 8);
            // If parent time is above global threshold
            if (DAT_00e44598 < fVar1) {
                // Update current bone's blend weight: parent time / divisor + base blend time
                *(float*)(this + 0xc0 + localBoneIndex * 4) = fVar1 / _DAT_011260b0 + *(float*)(this + 0x78);
            }
        }
        // Call a global callback if set
        if (DAT_01205578 != (code*)0x0) {
            DAT_01205578();
        }
    }
}